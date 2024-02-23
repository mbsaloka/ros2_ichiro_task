import launch
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_parameters',
            executable='my_node',
            name='my_node',
            namespace='/my_node',
            parameters=[{'x': 1.2}, {'y': 2.3}, {'w': 3.4}],
        )
    ])
