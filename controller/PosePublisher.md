`publish_link_pose` : Set to true to publish link pose 

`publish_visual_pose` : Set to true to publish visual pose 

`publish_collision_pose` : Set to true to publish collision pose 

`publish_sensor_pose` : Set to true to publish sensor pose 

`publish_model_pose` : Set to true to publish model pose. 

`publish_nested_model_pose` : Set to true to publish nested model pose. The pose of the model that contains this system is also published unless publish_model_pose is set to false 

`use_pose_vector_msg` : Set to true to publish an `ignition::msgs::Pose_V` message instead of mulitple `ignition::msgs::Pose` messages. 

`update_frequency` : Frequency of pose publications in Hz. A negative frequency publishes as fast as possible (i.e, at the rate of the simulation step) 

`static_publisher` : Set to true to publish static poses on a "<scoped_entity_name>/pose_static" topic. This will cause only dynamic poses to be published on the "<scoped_entity_name>/pose" topic. 

`static_update_frequency` : Frequency of static pose publications in Hz. A negative frequency publishes as fast as possible (i.e, at the rate of the simulation step).