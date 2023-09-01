#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <google/protobuf/wrappers.pb.h>
#include "wifi.hpp"

using namespace std;

const char* fields[11] = {
    "interface",
    "status",
    // iw_quality fields
    "link",
    "level",
    "noise",
    // iw_discarded fields
    "nwid",
    "crypt",
    "frag",
    "nwid",
    "misc",
    // iw_missed
    "beacon",
};
const unsigned int nfields = sizeof(fields) / sizeof(fields[0]);

vector<string> split(string& orig, char delim = ' ') {
    vector<string> tokens;
    boost::algorithm::split(tokens, orig, [delim](char c) { return c == delim; });
    vector<string> non_delim;
    copy_if(
        tokens.begin(), tokens.end(), back_inserter(non_delim),
        [](string& s) { return s.size() > 0; }
    );
    return non_delim;
}

/**
  * Read /proc/net/wireless + parse to dictionary.
  */
const char* read_wireless(google::protobuf::Struct* mutable_result) {
    ifstream source("/proc/net/wireless");
    vector<string> lines;
    string line;
    while (getline(source, line)) {
        lines.push_back(line);
    }
    if (lines.size() != 3) {
        cerr << "unexpected line count " << lines.size() << endl;
        return "Unexpected line count";
    }
    auto tokens = split(lines[2]);
    if (tokens.size() != nfields) {
        cerr << "unexpected token count " << tokens.size() << endl;
        return "Unexpected token count";
    }
    auto& retFields = *(mutable_result->mutable_fields());
    for (unsigned int i = 0; i < nfields; ++i) {
        google::protobuf::Value val;
        val.set_string_value(tokens[i]);
        retFields[fields[i]] = val;
    }
    return nullptr;
}
