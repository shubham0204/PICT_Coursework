#include <vector>
#include "process.hpp"

class Metrics {

    public:

    static float getAverageTAT( std::vector<Process> processes ) {
        float sum = 0.0f;
        for( Process p : processes ) {
            sum += p.turnAroundTime;
        }
        return sum / processes.size() ; 
    }

    static float getAverageWT( std::vector<Process> processes ) {
        float sum = 0.0f;
        for( Process p : processes ) {
            sum += p.waitTime;
        }
        return sum / processes.size() ; 
    }

} ; 