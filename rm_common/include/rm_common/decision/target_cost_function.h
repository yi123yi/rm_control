//
// Created by kiana on 2021/3/22.
//

#ifndef RM_COMMON_TARGET_COST_FUNCTION_H_
#define RM_COMMON_TARGET_COST_FUNCTION_H_

#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <rm_msgs/TrackData.h>
#include <rm_msgs/TrackDataArray.h>
#include <geometry_msgs/Twist.h>
#include <map>
#include "rm_common/referee/data.h"

namespace rm_common {
struct TargetState {
  int id{};
  double pos_x{}, pos_y{}, pos_z{};
  double vel_x{}, vel_y{}, vel_z{};
  ros::Time last_receive_;
};

class TargetCostFunction {
 public:
  explicit TargetCostFunction(ros::NodeHandle &nh, const RefereeData &referee_data);
  double costFunction(const rm_msgs::TrackDataArray &track_data_array);
  double costFunction(const TargetState &target_state);
  int getId() const { return optimal_id_; };

 private:
  double k_pos_{}, k_vel_{}, k_hp_{}, k_freq_{}, timeout_{};
  const RefereeData &referee_data_;
  int optimal_id_{};
  std::map<int, TargetState> id2target_states_;
  ros::Time last_switch_target_;
};
}
#endif // RM_COMMON_TARGET_COST_FUNCTION_H_