
#include "repository.h"
#include <fstream>
#include <sstream>

void Repository::loadFromFile() {
    items.clear();

    ifstream in(file_name);
    if (!in.is_open()) {
        throw runtime_error("Can't open file: " + file_name);
    }

    string line;
    while (getline(in, line)) {
        stringstream line_stream(line);

        string current;
        vector<string> split;

        while (getline(line_stream, current, ',')) {
            split.push_back(current);
        }

        if (split.size() == 3) {
            int id = stoi(split[0]);
            string description = split[1];

            stringstream prog_stream(split[2]);

            string curr;
            vector<string> programmers;

            while (getline(prog_stream, curr, ';')) {
                programmers.push_back(curr);
            }

            string status = programmers.back();
            programmers.pop_back();

            Task task(id, description, programmers, status);
            items.push_back(task);
        }
    }

    in.close();
}

void Repository::writeToFile() {
    ofstream out(file_name);

    for (const auto &prod : items) {
        out << prod.getId() << "," << prod.getDescription() << ",";

        for (const auto &programmer : prod.getProgrammers()) {
            out << programmer << ";";
        }

        out << prod.getStatus() << "\n";
    }

    out.close();
}

void Repository::addTask(const Task &task) {
    items.push_back(task);
    writeToFile();
}

bool Repository::findTask(int id) {
    auto it = find_if(items.begin(), items.end(), [id](const Task &t) {
        return t.getId() == id;
    });

    return it != items.end();
}

void Repository::setTaskStatus(int id, const string &status) {
    auto it = find_if(items.begin(), items.end(), [id](const Task &t) {
        return t.getId() == id;
    });

    it->setStatus(status);
    writeToFile();
}
