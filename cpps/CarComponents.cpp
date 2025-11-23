//
// Created by Carte on 23/11/2025.
//

#include "../header/CarComponents.h"
#include <algorithm>

float EngineSpec::getTorqueAtRpm(float rpm) const {
    if (torqueCurve.empty()) {
        // Fallback to flat torque if no curve defined
        return maxTorqueNM;
    }

    // Clamp the rpm to the torque curve
    if (rpm <= torqueCurve.front().first)
        return torqueCurve.front().second;
    if (rpm >= torqueCurve.back().first)
        return torqueCurve.back().second;

    // interpolate between the nearest points the torque curve
    for (std::size_t i = 0; i + 1 < torqueCurve.size(); ++i) {
        float x0 = torqueCurve[i].first;
        float y0 = torqueCurve[i].second;
        float x1 = torqueCurve[i + 1].first;
        float y1 = torqueCurve[i + 1].second;

        if (rpm >= x0 && rpm <= x1) {
            float t = (rpm - x0) / (x1 - x0);
            return y0 + t * (y1 - y0);
        }
    }

    // Fallback to non torque curve if something fails
    return maxTorqueNM;
}
