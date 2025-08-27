#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <tuple>

using OutputTuple = std::tuple<std::string, std::string, std::string, int>;

/** 
 * Load input and output from files, run an executable with the input, collect the executable's output on stdout and 
 * stderr, and return all three outputs for grading.
 * @param  executable_name The name of the executable. NOTE: It must be in the same path as the testing binary.
 * @param  output_file The path to a file containing the correct output for the executable relative to the input file.
 * @param  input_file The path to a file containing input for the executable, defaults to empty, meaning no input file.
 * @throws std::runtime_error on failure of any necessary system calls.
 * @return  A tuple with the correct output, the executable's output on stdout, the executable's output on stderr, and the
 *          executable's return code. NOTE: The return code is only accurate if within the range (-127, 127).
 */
OutputTuple getOutput(const std::string& executable_name, const std::string& output_file, 
                                                             const std::string& input_file = "") {
    // Load the input file if the path is not empty.
    std::string input_file_string;
    std::stringstream input_file_string_stream;
    if (input_file != "") {
        std::ifstream input_file_stream(input_file);
        if (!input_file_stream.is_open()) throw std::runtime_error("Failed to open input file");
        input_file_string = std::string(std::istreambuf_iterator<char>(input_file_stream), 
                                        std::istreambuf_iterator<char>());
        input_file_string_stream << input_file_string;
    }

    // Load the output file.
    std::ifstream output_file_stream(output_file);
    if (!output_file_stream.is_open()) throw std::runtime_error("Failed to open output file");
    std::string output_file_string;
    std::stringstream output_file_string_stream;
    output_file_string = std::string(std::istreambuf_iterator<char>(output_file_stream),
                                    std::istreambuf_iterator<char>());
    output_file_string_stream << output_file_string;

    // Create FIFOs for communicating with the executable.
    const char* fifo_stdin = "/tmp/fifo_stdin";
    const char* fifo_stdout = "/tmp/fifo_stdout";
    const char* fifo_stderr = "/tmp/fifo_stderr";
    mkfifo(fifo_stdin, 0666);
    mkfifo(fifo_stdout, 0666);
    mkfifo(fifo_stderr, 0666);

    // Fork the process so that the child can run the executable while being monitored. 
    std::stringstream output_string_stream;
    std::stringstream error_string_stream;
    int return_code = -2;
    pid_t pid = fork();
    if (pid == 0) {
        // Open and redirect the FIFOs in the child process to read on stdin and write on stdout and stderr.
        int fd_stdin = open(fifo_stdin, O_RDONLY);
        int fd_stdout = open(fifo_stdout, O_WRONLY);
        int fd_stderr = open(fifo_stderr, O_WRONLY);
        dup2(fd_stdin, STDIN_FILENO);
        dup2(fd_stdout, STDOUT_FILENO);
        dup2(fd_stderr, STDERR_FILENO);
        close(fd_stdin);
        close(fd_stdout);
        close(fd_stderr);

        // Replace the child process by running the executable.
        std::string command = "./" + executable_name;
        execl(command.c_str(), command.c_str(), "", nullptr);
        exit(127);
    } else if (pid > 0) {
        // Open the FIFOs in the parent process to write on stdin and read on stdout and stderr.
        int fd_stdin = open(fifo_stdin, O_WRONLY);
        int fd_stdout = open(fifo_stdout, O_RDONLY);
        int fd_stderr = open(fifo_stderr, O_RDONLY);

        // Write the contents of the input file to the stdin FIFO.
        std::string line;
        while (std::getline(input_file_string_stream, line)) {
            ssize_t write_size = 0;
            ssize_t total_write_size = 0;
            line += '\n';
            while (total_write_size < line.size()) {
                write_size = write(fd_stdin, line.c_str() + write_size, line.size() - write_size);
                total_write_size += write_size;
            }
        }
        close(fd_stdin);

        // Read the output of the executable on the stdout FIFO.
        char buffer[1024];
        ssize_t read_size;
        while ((read_size = read(fd_stdout, buffer, sizeof(buffer))) > 0) {
            output_string_stream.write(buffer, read_size);
        }
        close(fd_stdout);

        // Read the error output of the executable on the stderr FIFO.
        while ((read_size = read(fd_stderr, buffer, sizeof(buffer))) > 0) {
            error_string_stream.write(buffer, read_size);
        }
        close(fd_stderr);

        // Wait for the child process to finish, capture its return code, then clean up.
        int status;
        if (waitpid(pid, &status, 0) > 0) {
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                // Set the return code to indicate successful termination.
                return_code = 0;
            } else if (WIFEXITED(status) && WEXITSTATUS(status)) {
                if (WEXITSTATUS(status) == 127) {
                    throw std::runtime_error("Failed execl().");
                } else {
                    // Set the return code as accurately as possible given its last 8 bits. Only accurate (-127, 127).
                    if (WEXITSTATUS(status) > 127) {
                        return_code = WEXITSTATUS(status) - 256;
                    } else {
                        return_code = WEXITSTATUS(status);
                    }
                }
            } else {
                throw std::runtime_error("Child process terminated abnormally.");
            }
        } else {
            throw std::runtime_error("Failed waitpid().");
        }

        std::cout << std::endl << WEXITSTATUS(status) << std::endl;
        int return_code = WEXITSTATUS(status);
        unlink(fifo_stdin);
        unlink(fifo_stdout);
        unlink(fifo_stderr);
    } else {
        throw std::runtime_error("Failed to fork().");
    }
    std::tuple<std::string, std::string, std::string, int> outputs;
    std::get<0>(outputs) = output_file_string_stream.str();
    std::get<1>(outputs) = output_string_stream.str();
    std::get<2>(outputs) = error_string_stream.str();
    std::get<3>(outputs) = return_code;
    return outputs;
}
