# Use Drogon image from Docker Hub
FROM drogonframework/drogon

# Set the working directory in the container
WORKDIR /Redis-Alternative

# Copy your application files into the container
COPY . .

# Create a build directory
RUN mkdir -p build

# Move to the build directory and build the project
WORKDIR /Redis-Alternative/build

# Run cmake and make commands to build your project
RUN cmake .. && make

# Expose the Drogon default port
EXPOSE 8848

# Run your Drogon application (replace with your executable name)
CMD ["./RedisAlternative"]
