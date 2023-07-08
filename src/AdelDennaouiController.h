#pragma once

#include <mc_control/mc_controller.h>
#include <mc_tasks/CoMTask.h>
#include <mc_tasks/SurfaceTransformTask.h>
#include <mc_tasks/MetaTaskLoader.h>
#include <mc_tasks/LookAtFrameTask.h>
#include "api.h"

enum HandsPhase
{
      LEFT_HAND = 0,
      RIGHT_HAND,
      BOTH_HANDS,
      NO_HANDS
};

struct AdelDennaouiController_DLLAPI AdelDennaouiController : public mc_control::MCController
{
    AdelDennaouiController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

    bool run() override;

    void reset(const mc_control::ControllerResetData & reset_data) override;

    void switch_phase();
private:
    mc_rtc::Configuration config_;
    std::shared_ptr<mc_tasks::CoMTask> comTask;
    std::shared_ptr<mc_tasks::SurfaceTransformTask> handTaskL;
    std::shared_ptr<mc_tasks::SurfaceTransformTask> handTaskR;
    std::shared_ptr<mc_tasks::MetaTask> lookR_task;
    std::shared_ptr<mc_tasks::MetaTask> lookL_task;
    sva::PTransformd init_posL;
    sva::PTransformd init_posR;
    HandsPhase phase = NO_HANDS;
    HandsPhase previous_phase = BOTH_HANDS;
};