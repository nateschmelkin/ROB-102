import sys
import signal
import time
import os

import numpy as np
from joblib import dump, load  # To get the model to the robot

from sklearn.neighbors import KNeighborsClassifier
from sklearn import svm
from sklearn.neural_network import MLPClassifier

from mbot_bridge.api import MBot
from utils.camera import CameraHandler
from utils.robot import plan_to_pose, turn_to_theta
from waypoint_writer import read_labels_and_waypoints

# TODO: Update PATH_TO_MODEL.
PATH_TO_MODEL = "ml/model.joblib"

robot = MBot()


def signal_handler(sig, frame):
    print("Stopping...")
    robot.stop()
    sys.exit(0)


signal.signal(signal.SIGINT, signal_handler)


def main():
    ch = CameraHandler()  # Initialize the camera

    # NOTE: This code will fail if you have not updated PATH_TO_MODEL above.
    assert os.path.exists(PATH_TO_MODEL), f"Model file {PATH_TO_MODEL} does not exist."
    model = load(PATH_TO_MODEL)

    # Load labels and waypoints written by waypoint_writer.py
    labels, waypoints = read_labels_and_waypoints()  # labels: [0,1,2,...], waypoints: [[x,y,theta], ...]

    # Map from label -> index into waypoints list
    label_to_idx = {lbl: i for i, lbl in enumerate(labels)}

    # Assume robot starts at waypoint 0 (0-label location / start position)
    current_idx = 0
    start_x, start_y, start_theta = waypoints[0]

    print("Starting robot tour guide loop...")

    while True:
        # 1. Look for a post-it at the current location
        frame = None
        while frame is None:
            frame = ch.get_processed_image(save=True)
            if frame is None:
                print("No post-it detected, retrying...")
                time.sleep(0.2)  # Small delay to avoid spamming

        # 2. Use the model to predict the label
        #    Adjust this if your model expects a different shape than (1, -1).
        X = frame.reshape(1, -1)
        y_pred = model.predict(X)[0]
        print(f"Detected label: {y_pred}")

        # 3. If label is 0, return to start and exit
        if y_pred == 0:
            print("Label 0 detected. Returning to start and exiting.")
            plan_to_pose(start_x, start_y, robot)
            turn_to_theta(start_theta, robot)
            robot.stop()
            break

        # 4. If the predicted label is not one of the course labels, handle gracefully
        if y_pred not in label_to_idx:
            print(f"Predicted label {y_pred} not in course labels {labels}. Staying put and retrying.")
            time.sleep(1.0)
            continue

        # 5. Move to the waypoint corresponding to the predicted label
        next_idx = label_to_idx[y_pred]
        next_x, next_y, next_theta = waypoints[next_idx]
        print(f"Heading to waypoint index {next_idx}: ({next_x:.2f}, {next_y:.2f}, {next_theta:.2f})")

        plan_to_pose(next_x, next_y, robot)
        turn_to_theta(next_theta, robot)

        current_idx = next_idx
        # Loop continues: at the new waypoint we’ll look for a new post-it and repeat


if __name__ == '__main__':
    main()
