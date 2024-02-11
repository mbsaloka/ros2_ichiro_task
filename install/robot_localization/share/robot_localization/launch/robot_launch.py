import os
import launch
import subprocess
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

    robot_controller = launch.actions.ExecuteProcess(
        cmd=['gnome-terminal', '--geometry=50x12+100+800', '--', 'ros2', 'run', 'robot_localization', 'robot_controller'],
        output='screen'
    )

    object_recognizer = launch.actions.ExecuteProcess(
        cmd=['gnome-terminal', '--geometry=50x12+600+800', '--', 'ros2', 'run', 'robot_localization', 'object_recognizer'],
        output='screen'
    )

    # def close_terminals(event):
    #     subprocess.call(['pkill', 'gnome-terminal'])

    def close_terminals(event):
        # Menutup terminal robot_controller
        subprocess.call(['pkill', '-f', 'ros2 run robot_localization robot_controller'])
        # Menutup terminal object_recognizer
        subprocess.call(['pkill', '-f', 'ros2 run robot_localization object_recognizer'])



    return LaunchDescription([
        webots,
        my_robot_driver,
        robot_controller,
        object_recognizer,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=my_robot_driver,  # Attach event handler to my_robot_driver process
                on_exit=[
                    launch.actions.EmitEvent(event=launch.events.Shutdown()),
                    launch.actions.OpaqueFunction(function=close_terminals)
                ],
            )
        )
    ])
