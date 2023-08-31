#!/usr/bin/env bash
# apt-setup.sh -- install required apt packages

apt-get install -qqy \
	build-essential \
	libabsl-dev \
	libboost-all-dev \
	libgrpc++-dev \
	libprotobuf-dev \
	pkg-config \
	ninja-build \
	protobuf-compiler-grpc \
	git \
	wget
