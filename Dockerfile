FROM ubuntu:24.04

LABEL maintainer="https://github.com/user-unknowed/sth-chaos"
LABEL description="Multi-language coding environment with C, C++, and Python support"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    cmake \
    make \
    python3 \
    python3-pip \
    python3-dev \
    git \
    vim \
    wget \
    curl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root

RUN mkdir -p /root/coding

COPY . /root/coding/

RUN chown -R root:root /root/coding && \
    chmod -R 755 /root/coding && \
    find /root/coding -type f -name "*.sh" -exec chmod +x {} \; 2>/dev/null || true

RUN if [ -f /root/coding/requirements.txt ]; then \
        pip3 install --no-cache-dir -r /root/coding/requirements.txt; \
    fi

RUN if [ -f /root/coding/py/requirements.txt ]; then \
        pip3 install --no-cache-dir -r /root/coding/py/requirements.txt; \
    fi

WORKDIR /root/coding

CMD ["/bin/bash"]