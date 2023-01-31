#ifndef _TRAIN_HPP_
#define _TRAIN_HPP_

#include <iostream>
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>

//#include "netImpl.hpp"
#include "torch/torch.h"

//const std::string DATA_ROOT = std::string(EXCUTABLE_OUTPUT_PATH) + std::string("/data");
std::string DATA_ROOT;

const int64_t TRAIN_BATCH_SIZE = 64;
const int64_t TEST_BATCH_SIZE = 1000;
const int64_t NUMBER_OF_EPOCHS = 10;
const int64_t LOG_INTERVAL = 10;

#endif //_TRAIN_HPP_
