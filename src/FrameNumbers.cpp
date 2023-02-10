#include "FrameNumbers.h"

int const FrameNumbers::BYTE_SIZE = 2;
std::string const FrameNumbers::AEFE_TYPE = "AEFE";

const int FrameNumbers::PREAMBLE[] = {0, 8*BYTE_SIZE};
const int FrameNumbers::SOURCE[] = {16, 6*BYTE_SIZE};
const int FrameNumbers::DESTINATION[] = {28, 6*BYTE_SIZE};
const int FrameNumbers::TYPE[] = {40, 2*BYTE_SIZE};         
const int FrameNumbers::FCS[] = {-1, 4*BYTE_SIZE};          // The index is calcualted based on the packet size
const int FrameNumbers::PROTOCOL_VER[] = {44, 1};
const int FrameNumbers::CONCAT_INDICATOR[] = {45, 1};
const int FrameNumbers::MESSAGE_TYPE[] = {46, BYTE_SIZE};
const int FrameNumbers::PAYLOAD_SIZE[] = {48, 2*BYTE_SIZE};
const int FrameNumbers::RTC_ID[] = {52, 2*BYTE_SIZE};
const int FrameNumbers::SEQUENCE_ID[] = {56, 2*BYTE_SIZE};