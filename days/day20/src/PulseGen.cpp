#include "PulseGen.h"
#include <ranges>
#include <iostream>
#include <numeric>
void FlipFlop::apply(const Pulse &pulse, const std::string &from, std::queue<Signal> &queue) {
    (void) from; // ignore unused
    if (pulse == LOW) {
        m_state["state"] = !m_state["state"];
        Pulse sendvalue = m_state["state"] ? HIGH : LOW;
        for (auto &x: m_output) {
            queue.push({x, m_name, sendvalue});
        }
    }
};

void Conjunction::apply(const Pulse &pulse, const std::string &from, std::queue<Signal> &queue) {
    m_state[from] = (pulse == HIGH);
    bool all_high = true;
    for (auto &x: m_state) {
        if (!x.second) {
            all_high = false;
            break;
        }
    }
    Pulse sendvalue = all_high ? LOW : HIGH;
    for (auto &x: m_output) {
        queue.push({x, m_name, sendvalue});
    }
}


void Conjunction::addInput(const std::string &name) {
    m_state[name] = false;
}

PulseGen::PulseGen(std::istream &in) {
    for (std::string x; std::getline(in, x);) {
        char type = x[0];
        bool broadcaster = (type == 'b');
        auto offset = x.find(" ");
        std::string name = x.substr(1, offset - 1);
        if (type == '%') { m_members[name] = std::make_unique<FlipFlop>(name); }
        else if (type == '&') { m_members[name] = std::make_unique<Conjunction>(name); }
        offset = x.find(">") + 2;
        auto noffset = x.find(",", offset);
        while (noffset != std::string::npos) {
            std::string out = x.substr(offset, noffset - offset);
            if (broadcaster) { m_broadcast.push_back(out); }
            else { m_members[name]->addOutput(out); }
            offset = noffset + 2;
            noffset = x.find(",", offset);
        }
        std::string out = x.substr(offset);
        if (broadcaster) { m_broadcast.push_back(out); }
        else { m_members[name]->addOutput(out); }
    }

    for (auto const &m: m_members) {
        for (auto const &o: m.second->getOutputs()) {
            if (m_members.contains(o)) {
                m_members[o]->addInput(m.first);
            }
        }
    }
    for (auto const &o: m_broadcast) {
        if (m_members.contains(o)) {
            m_members[o]->addInput("broadcast");
        }
    }
}



std::pair<unsigned long int,unsigned long int> PulseGen::run(bool skip_rx) {
    unsigned long int low_cnt = 0;
    unsigned long int high_cnt = 0;
    unsigned long int rx_loc = 0;
    bool rx_found = skip_rx;
    unsigned long int vn, hn,kt,ph;
    bool vn_found(false), hn_found(false),kt_found(false),ph_found(false);
    bool run_done = false;
    unsigned long int i = 0;
    while (!run_done || !rx_found) {
        if (!run_done) {low_cnt++;} //button press
        std::queue<Signal> s;
        for (auto const &t: m_broadcast) {
            s.push({t, "broadcast", LOW});
        }
        while (!s.empty()) {
            auto cmd = s.front();
            s.pop();
            if (!run_done) {
                if (std::get<2>(cmd) == HIGH) { high_cnt++; }
                else { low_cnt++; }
            }
            //finding rx (i hate this)
            if(!vn_found && std::get<1>(cmd) == "vn" && std::get<2>(cmd) == HIGH) {
                vn = i+1;
                vn_found = true;
            }
            if(!hn_found && std::get<1>(cmd) == "hn" && std::get<2>(cmd) == HIGH) {
                hn = i+1;
                hn_found = true;
            }
            if(!kt_found && std::get<1>(cmd) == "kt" && std::get<2>(cmd) == HIGH) {
                kt = i+1;
                kt_found=true;
            }
            if(!ph_found && std::get<1>(cmd) == "ph" && std::get<2>(cmd) == HIGH) {
                ph = i+1;
                ph_found=true;
            }
            if(vn_found && hn_found && kt_found && ph_found ) {
                rx_found = true;
                rx_loc = std::lcm(vn, std::lcm(ph, std::lcm( hn, kt)));
            }
            if (m_members.contains(std::get<0>(cmd))) {
                m_members[std::get<0>(cmd)]->apply(std::get<2>(cmd), std::get<1>(cmd), s);
            };
        }
        i++;
        if (i == 1000) {run_done = true;}
    }
    return {high_cnt * low_cnt, rx_loc};
}