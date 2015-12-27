
http://qmlbook.org/ch05/index.html

--------------------------------------------------------------------------------

# Animations

 An animation is defined by a series of target properties to be animated, an
easing curve for the interpolation curve and in the most cases a duration, which
defines the time for the property change.

Animations control how property changes, i.e. value interpolation. This is a
fundamental concept. QML is based on elements, properties and scripting. Every
element provides dozens of properties, each property is waiting to get animated
by you.


There are several types of animation elements, each optimized for a specific use
case. Here is a list of the most prominent animations:

PropertyAnimation - Animates changes in property values
NumberAnimation - Animates changes in qreal-type values
ColorAnimation - Animates changes in color values
RotationAnimation - Animates changes in rotation values



QtQuick provides also more specialized animations for specific use cases:

PauseAnimation - Provides a pause for an animation
SequentialAnimation - Allows animations to be run sequentially
ParallelAnimation - Allows animations to be run in parallel
AnchorAnimation - Animates changes in anchor values
ParentAnimation - Animates changes in parent values
SmoothedAnimation - Allows a property to smoothly track a value
SpringAnimation - Allows a property to track a value in a spring-like motion
PathAnimation - Animates an item along a path
Vector3dAnimation - Animates changes in QVector3d values


QtQuick offers the action elements, which can be used everywhere where the other
animation elements can be used:

PropertyAction - Specifies immediate property changes during animation
ScriptAction - Defines scripts to be run during an animation



Animation can be applied in several ways:

Animation on property - runs automatically after element is fully loaded
Behavior on property - runs automatically when the property value changes
Standalone Animation - runs when animation is explicitly started using start()
or running is set to true (e.g. by a property binding)

--------------------------------------------------------------------------------














