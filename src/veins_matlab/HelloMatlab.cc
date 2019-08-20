//
// Copyright (C) 2019 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <iostream>

#include "HelloMatlab.h"

#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"

namespace {
std::unique_ptr<matlab::engine::MATLABEngine> matlabEngine;
}

Define_Module(HelloMatlab);

void HelloMatlab::initialize()
{
    EV_DEBUG << "connecting to engine" << std::endl;
    try {
        matlabEngine = matlab::engine::connectMATLAB(u"veins");
    }
    catch (const matlab::engine::EngineException& e) {
        EV_DEBUG << std::endl;
        EV_DEBUG << "!! Cannot connect to MATLAB session." << std::endl;
        EV_DEBUG << "!!" << std::endl;
        EV_DEBUG << "!! Please run\n>> matlab.engine.shareEngine('veins')\n!! in a MATLAB session and keep this session running" << std::endl;
        EV_DEBUG << std::endl;
        throw;
    }
    EV_DEBUG << "done connecting to engine" << std::endl;

    auto callback = [this]() {
        int i = testFunction(simTime().dbl(), 10);
        EV_INFO << "MATLAB result is " << i << std::endl;
    };
    timerManager.create(veins::TimerSpecification(callback).absoluteStart(SimTime(1, SIMTIME_S)).interval(SimTime(1, SIMTIME_S)).repetitions(3));
}

void HelloMatlab::finish()
{
    EV_INFO << "finishing" << std::endl;
    matlabEngine.reset();
}

void HelloMatlab::handleMessage(cMessage* msg)
{
    if (timerManager.handleMessage(msg)) return;
}

double HelloMatlab::testFunction(double i, double j)
{
    matlab::data::ArrayFactory factory;

    auto arg3 = factory.createArray({1, 1}, {i});
    auto arg4 = factory.createArray({1, 1}, {j});
    auto ra = matlabEngine->feval(u"testFunction", {arg3, arg4});
    if (ra.getNumberOfElements() != 1) {
        throw cRuntimeError("MATLAB returned no result where one was expected");
    }
    double r = ra[0];

    return r;
}
