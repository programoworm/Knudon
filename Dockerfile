# Use an official GCC image
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Copy all files to the container
COPY . .

# Compile the project
RUN g++ -o knudon main.cpp scanner.cpp parser.cpp interpreter.cpp statements.cpp

# Default command
CMD ["./knudon", "edge_case_default.k"]
