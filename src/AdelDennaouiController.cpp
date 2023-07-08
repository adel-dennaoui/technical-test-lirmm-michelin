#include "AdelDennaouiController.h"

AdelDennaouiController::AdelDennaouiController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController(rm, dt)
{
  config_.load(config);
  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(dynamicsConstraint);
  solver().addTask(postureTask);
  addContact({robot().name(), "ground", "LeftFoot", "AllGround"});
  addContact({robot().name(), "ground", "RightFoot", "AllGround"});
  comTask = std::make_shared<mc_tasks::CoMTask>(robots(), 0, 10.0, 1000.0);
  solver().addTask(comTask);
  postureTask->stiffness(1);

  mc_rtc::log::success("AdelDennaouiController init done ");
}

bool AdelDennaouiController::run()
{
  switch_phase();
  return mc_control::MCController::run();
}

void AdelDennaouiController::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);
  comTask->reset();
  
  handTaskL = std::make_shared<mc_tasks::SurfaceTransformTask>("l_wrist", robots(), 0);
  handTaskR = std::make_shared<mc_tasks::SurfaceTransformTask>("r_wrist", robots(), 0);
  lookR_task = mc_tasks::MetaTaskLoader::load(solver(), "/home/wsl-ros/adel_dennaoui_controller/src/lookR.yaml");
  lookL_task = mc_tasks::MetaTaskLoader::load(solver(), "/home/wsl-ros/adel_dennaoui_controller/src/lookL.yaml"); 
  solver().addTask(handTaskL);
  solver().addTask(handTaskR);
  solver().addTask(lookL_task);
  init_posR = handTaskR->target();
  init_posL = handTaskL->target();
  handTaskL->target(sva::PTransformd(Eigen::Quaterniond(0.7, 0, 0.7, 0), Eigen::Vector3d(0.5, 0.25, 1.1)));
}

void AdelDennaouiController::switch_phase()
{
  if(phase == LEFT_HAND && handTaskL->eval().norm() < 0.2 && handTaskL->speed().norm() < 1e-2)
  { 
    solver().removeTask(lookL_task);
    handTaskL->target(sva::PTransformd(init_posL));
    phase = NO_HANDS;
    previous_phase = LEFT_HAND;
  }
  else if(phase == RIGHT_HAND && handTaskR->eval().norm() < 0.2 && handTaskR->speed().norm() < 1e-2)
  { 
    solver().removeTask(lookR_task);
    handTaskR->target(sva::PTransformd(init_posR));
    phase = NO_HANDS;
    previous_phase = RIGHT_HAND;
  }
  else if(phase == BOTH_HANDS && handTaskL->eval().norm() < 0.2 && handTaskL->speed().norm() < 1e-2 && handTaskR->eval().norm() < 0.2 && handTaskR->speed().norm() < 1e-2)
  {
    handTaskL->target(sva::PTransformd(init_posL));
    handTaskR->target(sva::PTransformd(init_posR));
    phase = NO_HANDS;
    previous_phase = BOTH_HANDS;
  }
  else if(phase == NO_HANDS){
    if(previous_phase == LEFT_HAND && handTaskL->eval().norm() < 0.2 && handTaskL->speed().norm() < 1e-2){
      solver().addTask(lookR_task);
      handTaskR->target(sva::PTransformd(Eigen::Quaterniond(0.7, 0, 0.7, 0), Eigen::Vector3d(0.5, -0.25, 1.1)));
      phase = RIGHT_HAND;
    }
    else if(previous_phase == RIGHT_HAND && handTaskR->eval().norm() < 0.2 && handTaskR->speed().norm() < 1e-2){
      handTaskL->target(sva::PTransformd(Eigen::Quaterniond(0.7, 0, 0.7, 0), Eigen::Vector3d(0.5, 0.25, 1.1)));
      handTaskR->target(sva::PTransformd(Eigen::Quaterniond(0.7, 0, 0.7, 0), Eigen::Vector3d(0.5, -0.25, 1.1)));
      phase = BOTH_HANDS;
    }
    else if(previous_phase == BOTH_HANDS && handTaskL->eval().norm() < 0.2 && handTaskL->speed().norm() < 1e-2 && handTaskR->eval().norm() < 0.2 && handTaskR->speed().norm() < 1e-2)
    { 
      solver().addTask(lookL_task);
      handTaskL->target(sva::PTransformd(Eigen::Quaterniond(0.7, 0, 0.7, 0), Eigen::Vector3d(0.5, 0.25, 1.1)));
      phase = LEFT_HAND;
    }
  }
}

CONTROLLER_CONSTRUCTOR("AdelDennaouiController", AdelDennaouiController)