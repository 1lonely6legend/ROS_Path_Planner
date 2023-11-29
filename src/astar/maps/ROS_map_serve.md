# ROS map_serve

## 大致介绍

https://wiki.ros.org/map_server

> ROS（Robot Operating System）中的 `map_server` 是一个提供地图服务的功能包。它主要用于处理机器人应用中的地图数据，包括加载、保存、转换和提供地图。`map_server` 在许多机器人应用中发挥着重要作用，尤其是在需要地图数据进行导航和路径规划的场景中。

### 具体作用与功能

1. **加载地图**：`map_server` 可以加载一个保存为YAML文件格式的地图。这个YAML文件通常包含对实际地图数据的引用，地图数据通常以PGM（Portable Graymap Format）或其他图像格式存储。
2. **提供地图服务**：加载地图后，`map_server` 会提供ROS主题（topics）和服务（services），允许其他ROS节点获取地图数据。这对于在ROS环境中进行导航和路径规划至关重要。
3. **地图转换**：`map_server` 可以将地图数据转换成适合ROS使用的格式。例如，将PGM图像文件中的数据转换为ROS理解的地图消息格式。
4. **保存地图**：`map_server` 还可以将ROS中的地图数据保存为图像文件和YAML文件，方便将来使用或分享。

### 传入参数

`map_server` 的运行需要一些参数，这些参数通常通过命令行或启动文件（launch file）传递：

1. **地图文件**：需要指定一个YAML文件，该文件描述了地图的位置、尺寸和分辨率。YAML文件通常包含对实际地图图像文件（如PGM文件）的引用。

使用`map_server` 时，通常需要结合ROS的其他功能包和工具，如`rviz`（用于可视化地图）和`amcl`（用于定位和地图创建）。它是ROS导航堆栈中的关键组件，为机器人提供了一个基础的地图处理能力。

## yaml文件配置

```yaml
image: testmap.png
resolution: 0.1
origin: [0.0, 0.0, 0.0]
occupied_thresh: 0.65
free_thresh: 0.196
negate: 0
```

- image:指定包含occupancy data的image文件路径; 可以是绝对路径，也可以是相对于YAML文件的对象路径 。
- resolution:地图分辨率，单位是meters/pixel 。
- origin:图中左下角像素的二维位姿，如（x，y，yaw），yaw逆时针旋转(yaw=0表示没有旋转)。系统的很多部分现在忽略yaw值。注意fix_frame是map
- occupied_thresh:像素占用率大于这个阈值则认为完全占用。
- free_thresh:像素占用率比该阈值小被则认为完全自由。
- negate:无论白色或黑色，占用或自由，语义应该是颠倒的（阈值的解释不受影响）。

## 具体使用方法

在启动roscore的情况下，在终端中输入

```shell
rosrun map_server map_server map.yaml
```

## 输出话题

在ROS中，`map_server` 节点输出两个主要的话题：`/map` 和 `/map_metadata`。这两个话题共同提供了地图的完整信息，但它们的内容和用途有所不同。

1. ### **/map 话题**：

   - `/map` 话题发布的是地图的实际数据。这通常是一个二维的栅格地图，用于表示环境。
   - 地图以 `nav_msgs/OccupancyGrid` 消息类型发布。这种消息类型包含了栅格地图的每个单元格的状态，其中每个单元格可能表示为障碍物、自由空间或未知区域。
   - ros 具体定义：https://docs.ros.org/en/noetic/api/nav_msgs/html/msg/OccupancyGrid.html
   - 这个话题对于执行导航和路径规划的机器人节点至关重要，因为它提供了环境的实际空间表示。

```rosmsg
std_msgs/Header header
nav_msgs/MapMetaData info   
int8[] data     //一维数据，存放的是地图坐标点上的栅栏属性，范围为(0,100)，其中0为可通过，100为障碍物
                //在map中显示就是0为白色，100为黑色，但是一维数据实际上是由二维数据变换来的，这个变换过程可以参考
                //https://www.bilibili.com/video/BV1uD4y1z74h
```

1. ### **/map_metadata 话题**：

   - `/map_metadata` 话题发布的是与地图相关的元数据。元数据包含了地图的额外信息，但不包括地图的实际栅格数据。
   - 元数据以 `nav_msgs/MapMetaData` 消息类型发布。这种消息类型包含了地图的尺寸、分辨率、地图的原点（在世界坐标系中的位置），以及地图的时间戳。
   - 这个话题对于理解地图的上下文和空间参数非常重要。例如，它告诉机器人地图中一个单元格的实际物理尺寸，以及地图在世界坐标系中的定位。

```rosmsg
geometry_msgs/Point position    //栅格地图在上面相对应的坐标系下的坐标，含有x，y，z，这个是我们需要的
geometry_msgs/Quaternion orientation  //四元数，二维用不上，先不管，后面三维会用到
```

## 设置起始点

rviz中设置起始点

使用的消息为`geometry_msgs/PoseWithCovarianceStamped`

```
std_msgs/Header header 
  uint32 seq                //帧数
  time stamp                //时间戳
  string frame_id           //地图参考的坐标系id
geometry_msgs/PoseWithCovariance pose
  geometry_msgs/Pose pose
    geometry_msgs/Point position  //位置
      float64 x
      float64 y
      float64 z
    geometry_msgs/Quaternion orientation  //四元数姿态
      float64 x
      float64 y
      float64 z
      float64 w
  float64[36] covariance //描述位置不确定的协方差矩阵，具体的顺序为(x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)
```

## 设置终点

rviz中设置终点

使用的消息为`/move_base_simple/goal`

```
std_msgs/Header header
  uint32 seq                //帧数
  time stamp                //时间戳
  string frame_id           //地图参考的坐标系id
geometry_msgs/Pose pose
  geometry_msgs/Point position   //位置
    float64 x
    float64 y
    float64 z
  geometry_msgs/Quaternion orientation    //四元数姿态
    float64 x
    float64 y
    float64 z
    float64 w
```

