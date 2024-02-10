import os
import launch
from launch_ros.actions import Node
from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from webots_ros2_driver.webots_launcher import WebotsLauncher
from webots_ros2_driver.webots_controller import WebotsController


def generate_launch_description():
    package_dir = get_package_share_directory('robot_localization')
    robot_description_path = os.path.join(package_dir, 'resource', 'my_robot.urdf')

    webots = WebotsLauncher(
        world=os.path.join(package_dir, 'worlds', 'soccer_field.wbt')
    )

    my_robot_driver = WebotsController(
        robot_name='my_epuck',
        parameters=[
            {'robot_description': robot_description_path},
        ]
    )

    # robot_controller = Node(
    #     package='robot_localization',
    #     executable='robot_controller',
    #     output='screen',
    # )   

    robot_controller = launch.actions.ExecuteProcess(
        cmd=['gnome-terminal', '--', 'ros2', 'run', 'robot_localization', 'robot_controller'],
        output='screen'
    )

    return LaunchDescription([
        webots,
        my_robot_driver,
        robot_controller,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=webots,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )
        )
    ])