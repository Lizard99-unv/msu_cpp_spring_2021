#pragma once

#include <fstream>
#include <string>

#define BUF_SIZE 1000000

void AssignFiles(std::ifstream& prev_res, std::ofstream& new_res,
                 const std::string& prev_name, const std::string& new_name);

bool WriteFromBuffer(std::ofstream& new_res, const uint64_t * const buffer,
                     size_t& cur_dig_num, size_t& cur_mid_num,
                     size_t amount, bool something_written);

void MergeFileAndBuffer(std::ifstream& prev_res, std::ofstream& new_res,
                        const uint64_t * const buffer, size_t amount);

void AddToFile (const uint64_t * const buffer, const std::string& dir, int step, size_t amount);

void PrepareFiles(const std::string& filepath,
                  std::string& dir, std::string& name);

int ProcessFiles(std::ifstream& inp, const std::string& dir);

std::string SortFile (std::string filepath);