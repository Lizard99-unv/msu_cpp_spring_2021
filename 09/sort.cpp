#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>

#include <iostream>
#include <vector>

#include "sort.hpp"

void AssignFiles(std::ifstream& prev_res, std::ofstream& new_res,
                 const std::string& prev_name, const std::string& new_name) {
  prev_res.open(prev_name);
  if (!prev_res.is_open()) { 
    throw std::runtime_error("Input file opening failed");
  }
  new_res.open(new_name);
  if (!new_res.is_open()) { 
    throw std::runtime_error("Output file opening failed");
  }
}

bool WriteFromBuffer(std::ofstream& new_res, const uint64_t * const buffer,
                     size_t& cur_dig_num, size_t& cur_mid_num,
                     size_t amount, bool something_written) {

  if (cur_dig_num < amount / 2 && (cur_mid_num >= amount ||
      buffer[cur_dig_num] < buffer[cur_mid_num])) {
    if (something_written) {
      new_res << std::endl;
    }
    new_res << buffer[cur_dig_num];
    something_written = true;
    cur_dig_num++;
  } else if (cur_mid_num < amount) {
    if (something_written) {
      new_res << std::endl;
    }
    new_res << buffer[cur_mid_num];
    something_written = true;
    cur_mid_num++;
  }
  return something_written;
}

void MergeFileAndBuffer(std::ifstream& prev_res, std::ofstream& new_res,
                        const uint64_t * const buffer, size_t amount) {
  size_t cur_dig_num = 0;
  size_t cur_mid_num = amount / 2;
  bool something_written = false;
  while (prev_res.peek() != EOF || cur_dig_num < amount / 2 || cur_mid_num < amount) {
    bool read_num = false;
    uint64_t cur_file_num = 0;
    if (prev_res.peek() != EOF) {
      prev_res >> cur_file_num;
      read_num = true;
    }
    while ((cur_dig_num < amount / 2 && cur_file_num > buffer[cur_dig_num]) ||
           (cur_mid_num < amount && cur_file_num > buffer[cur_mid_num]) ||
           (!read_num && (cur_dig_num < amount / 2 || cur_mid_num < amount))) {
      something_written = WriteFromBuffer(new_res, buffer, cur_dig_num,
                                          cur_mid_num, amount, something_written);
    }
    if (read_num) {
      if (something_written) {
        new_res << std::endl;
      }
      new_res << cur_file_num;
      something_written = true;
    }
  }
}

void AddToFile (const uint64_t * const buffer, const std::string& dir, int step, size_t amount) {
  std::ifstream prev_res;
  std::ofstream new_res;
  if (step == 0) {
    AssignFiles(prev_res, new_res, dir + "odd_step_res.txt", dir + "even_step_res.txt");
  } else {
    AssignFiles(prev_res, new_res, dir + "even_step_res.txt", dir + "odd_step_res.txt");
  }
  new_res << std::unitbuf;

  MergeFileAndBuffer(prev_res, new_res, buffer, amount);

  prev_res.close();
  new_res.close();
  if (step == 1) {
    std::remove((dir + "even_step_res.txt").c_str());
  } else {
    std::remove((dir + "odd_step_res.txt").c_str());
  }
}

void PrepareFiles(const std::string& filepath,
                  std::string& dir, std::string& name) {

  std::string_view dir_view = filepath;

  size_t pos = dir_view.find_last_of('/');
  dir_view.remove_suffix(dir_view.size() - pos - 1);

  dir = std::string(dir_view);

  std::string_view name_view = filepath;

  if (pos != dir_view.npos) {
    name_view.remove_prefix(pos);
  }

  size_t name_pos = name_view.find_last_of('.');
  name_view.remove_suffix(name_view.size() - name_pos);

  name = std::string(name_view);

  std::ofstream(dir + "odd_step_res.txt").close();
  std::ofstream(dir + "even_step_res.txt").close();
}

int ProcessFiles(std::ifstream& inp, const std::string& dir) {
  int step_counter = 0;
  while (inp.peek() != EOF) {
    // std::array<uint64_t, BUF_SIZE> buffer;
    uint64_t *buffer = new uint64_t[BUF_SIZE];
    size_t cur_amount = 0;
    while (cur_amount < BUF_SIZE && !inp.eof()) {
      inp >> buffer[cur_amount];
      cur_amount++;
    }

    if (inp.bad()) {
      throw std::runtime_error("I/O error while reading");
    }
    if (inp.fail()) {
      throw std::runtime_error("Non-integer data encountered");
    }

    std::thread thread_first_half([buffer, cur_amount]() {
      std::sort(buffer, buffer + cur_amount / 2);
    });
    std::thread thread_second_half([buffer, cur_amount]() {
      std::sort(buffer + cur_amount / 2, buffer + cur_amount);
    });

    thread_first_half.join();
    thread_second_half.join();

    AddToFile(buffer, dir, step_counter, cur_amount);
    step_counter = (step_counter + 1) % 2;
  }
  return step_counter;
}

std::string SortFile (std::string filepath) {
  std::ifstream inp(filepath);
  if (!inp) { 
    throw std::runtime_error("Input file opening failed::" + filepath);
  }

  std::string dir;
  std::string name;
  PrepareFiles(filepath, dir, name);
  
  int step_counter = ProcessFiles(inp, dir);

  inp.close();

  if (step_counter == 1) {
    std::rename((dir + "even_step_res.txt").c_str(), (dir + name + "_sorted.txt").c_str());
    std::remove((dir + "odd_step_res.txt").c_str());
  } else {
    std::rename((dir + "odd_step_res.txt").c_str(), (dir + name + "_sorted.txt").c_str());
    std::remove((dir + "even_step_res.txt").c_str());
  }
  return name + "_sorted.txt";
}
