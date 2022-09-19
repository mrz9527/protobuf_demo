#! /bin/bash
protoc -I=./ --cpp_out=./ ClassInfo.proto
