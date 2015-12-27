/*
 *
 */

import QtQuick 2.0

Rectangle {
    id: root
    width: 600; height: 400

    Image {
        x: 12; y: 12
        source: "images/rocket.png"
    }

    Image {
        x: 112; y: 12
        width: 48
        height: 118/2
        source: "images/rocket.png"

        /* 图像元素（Image element）使用PreserveAspectCrop可以避免裁剪图像数据被
        渲染到图像边界外。默认情况下裁剪是被禁用的（clip:false）。
        你需要打开裁剪（clip:true）来约束边界矩形的绘制。*/
        fillMode: Image.PreserveAspectCrop
        clip: true
    }

}










