#pragma once
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <tuple>
#include <memory>


enum Pulse {
    LOW,
    HIGH
};

// TO, FROM, PULSE
using Signal = std::tuple<std::string, std::string, Pulse>;

class Unit {
public:
    virtual ~Unit() = default;
    unsigned int getState() const {
        unsigned int out = 0;
        for(auto const &x: m_state) {
            out <<=1;
            out |=x.second;
        }
        return out;
    };
    virtual void apply(const Pulse &pulse, const std::string &from, std::queue<Signal> &queue) = 0;
    virtual void addInput(const std::string &name) = 0;
    void addOutput(const std::string &name) {m_output.push_back(name);};
    std::vector<std::string> getOutputs() const {return m_output;};
protected:
    std::map<std::string, bool> m_state;
    std::vector<std::string> m_output;
    std::string m_name;
};

class FlipFlop : public Unit {
public:
    FlipFlop(const std::string &name)  {m_state= {{"state", false}}; m_name = name;};
    void apply(const Pulse &pulse, const std::string &from, std::queue<Signal> &queue) override;
    void addInput(const std::string &name) override {(void)name;}; // ignore
};


class Conjunction : public Unit {
public:
    Conjunction(const std::string &name) {m_name = name;};
    void apply(const Pulse &pulse, const std::string &from, std::queue<Signal> &queue) override;
    void addInput(const std::string &name) override;
};

class PulseGen {
public:
    PulseGen(std::istream &in);
    std::pair<unsigned long int,unsigned long int> run(bool skip_rx=true);
private:
    std::map<std::string, std::unique_ptr<Unit>> m_members;
    std::vector<std::string> m_broadcast;
};