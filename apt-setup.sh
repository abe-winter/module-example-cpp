#!/usr/bin/env bash
# apt-setup.sh -- install required apt packages

apt-get install -qqy \
	build-essential \
	libabsl-dev \
	libboost-all-dev \
        libboost-log1.74.0 \
	libgrpc++-dev \
        libgrpc++1 \
	libprotobuf-dev \
	pkg-config \
	ninja-build \
	protobuf-compiler-grpc \
	git \
	wget
