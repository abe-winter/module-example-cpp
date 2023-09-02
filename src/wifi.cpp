#include "wifi.hpp"

#include <google/protobuf/wrappers.pb.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** the field names in /proc/net/wireles */
const char *fields[11] = {
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

/** util: split a string by spaces */
vector<string> split(string &orig, char delim = ' ') {
    vector<string> tokens;
    boost::algorithm::split(tokens, orig, [delim](char c) { return c == delim; });
    vector<string> non_delim;
    copy_if(tokens.begin(), tokens.end(), back_inserter(non_delim), [](string &s) {
        return s.size() > 0;
    });
    return non_delim;
}

/** util: read lines from file */;
vector<string> readLines(const char *path) {
    vector<string> lines;
    ifstream source(path);
    string line;
    while (getline(source, line)) {
        lines.push_back(line);
    }
    return lines;
}

/** Read /proc/net/wireless + parse to dictionary */
viam::sdk::AttributeMap read_wireless() {
    auto lines = readLines("/proc/net/wireless");
    if (lines.size() != 3) {
        cerr << "unexpected line count " << lines.size() << endl;
        throw std::runtime_error("Unexpected line count in read_wireless");
    }
    auto tokens = split(lines[2]);
    if (tokens.size() != nfields) {
        cerr << "unexpected token count " << tokens.size() << endl;
        throw std::runtime_error("Unexpected token count in read_wireless");
    }
    auto map =
        std::make_shared<std::unordered_map<std::string, std::shared_ptr<viam::sdk::ProtoType>>>();
    for (unsigned int i = 0; i < nfields; ++i) {
        map->insert({
            std::string(fields[i]),
            std::make_shared<viam::sdk::ProtoType>(tokens[i]),
        });
    }
    return map;
}
