FROM ubuntu:22.04

RUN apt-get update


# Install LLVM + clang 17
RUN apt-get install -y lsb-release wget software-properties-common gnupg
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod u+x llvm.sh 
RUN ./llvm.sh 17

# Install Python 3
RUN apt-get install -y python3-dev python3-pip
RUN pip install -U --user pip

# Install Bazelisk
RUN wget https://github.com/bazelbuild/bazelisk/releases/download/v1.20.0/bazelisk-linux-amd64
RUN mkdir $HOME/bazelisk
RUN mv bazelisk-linux-amd64 $HOME/bazelisk/bazel
ENV PATH=$PATH:$HOME/bazelisk
RUN chmod +x $HOME/bazelisk/bazel

# Install CUDA 12.3
RUN wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-ubuntu2204.pin
RUN mv cuda-ubuntu2204.pin /etc/apt/preferences.d/cuda-repository-pin-600
RUN wget https://developer.download.nvidia.com/compute/cuda/12.3.0/local_installers/cuda-repo-ubuntu2204-12-3-local_12.3.0-545.23.06-1_amd64.deb
RUN dpkg -i cuda-repo-ubuntu2204-12-3-local_12.3.0-545.23.06-1_amd64.deb
RUN cp /var/cuda-repo-ubuntu2204-12-3-local/cuda-*-keyring.gpg /usr/share/keyrings/
RUN apt-get update
RUN apt-get -y install cuda-toolkit-12-3

# Install CUDNN 8.9.7
RUN apt-get install zlib1g
COPY cudnn-local-repo-ubuntu2204-8.9.7.29_1.0-1_amd64.deb /cudnn-local-repo-ubuntu2204-8.9.7.29_1.0-1_amd64.deb
RUN dpkg -i cudnn-local-repo-ubuntu2204-8.9.7.29_1.0-1_amd64.deb
RUN cp /var/cudnn-local-repo-*/cudnn-local-*-keyring.gpg /usr/share/keyrings/
RUN apt-get update
RUN apt-get -y install libcudnn8=8.9.7.29-1+cuda12.2

# # Install git
RUN apt-get install -y git

# # # Install TensorRT
RUN wget https://developer.nvidia.com/downloads/compute/machine-learning/tensorrt/10.3.0/local_repo/nv-tensorrt-local-repo-ubuntu2204-10.3.0-cuda-12.5_1.0-1_amd64.deb
RUN os="ubuntu2204"
RUN tag="10.3.0-cuda-12.5"
RUN dpkg -i nv-tensorrt-local-repo-ubuntu2204-10.3.0-cuda-12.5_1.0-1_amd64.deb
RUN cp /var/nv-tensorrt-local-repo-ubuntu2204-10.3.0-cuda-12.5/*-keyring.gpg /usr/share/keyrings/
RUN apt-get update
RUN apt-get install -y tensorrt