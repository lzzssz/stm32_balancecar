import time, os, sys
from media.sensor import *
from media.display import *
from media.media import *

import time
sensor = None

try:

        sensor = Sensor(width=640,height=640)
        sensor.reset()

        sensor.set_framesize(width=640,height=640)
        sensor.set_pixformat(Sensor.RGB565)

        # 使用IDE的帧缓冲区作为显示输出
        Display.init(Display.ST7701,width=800,height=480,to_ide=True)
        # 初始化媒体管理器
        MediaManager.init()
        # 启动传感器
        sensor.run()

        clock=time.clock()
        while True:
            #开始计次 为了显示帧率
            clock.tick()
            #便于退出停止
            os.exitpoint()
            img = sensor.snapshot(chn=CAM_CHN_ID_0)

            #处理图像黑白化
            img_rect=img.to_grayscale(copy=True)
            #图像二值化
            img_rect=img_rect.binary([(104, 166),(62, 167),(47, 186)])
            #寻找矩形代码
            rects=img_rect.find_rects(threshold=5000)

            for rect in rects:
                #用列表提取识别到的矩形坐标 再绘制出相应矩形
                corner=rect.corners()
                img.draw_line(corner[0][0],corner[0][1],corner[1][0],corner[1][1],thickness=5,color=(0,255,0))
                img.draw_line(corner[2][0],corner[2][1],corner[1][0],corner[1][1],thickness=5,color=(0,255,0))
                img.draw_line(corner[2][0],corner[2][1],corner[3][0],corner[3][1],thickness=5,color=(0,255,0))
                img.draw_line(corner[0][0],corner[0][1],corner[3][0],corner[3][1],thickness=5,color=(0,255,0))



            img.draw_string_advanced(50,30,80,"FPS={}".format(clock.fps()),color=(255,0,0))
            #缩小图像单位，变为原来的1/2
            img.midpoint_pool(2,2)

            #为了让他适应缓冲区
            img.compressed_for_ide()
            Display.show_image(img)
            #让画面再lcd上居中显示
            Display.show_image(img,x=(800-320)//2,y=(480-320)//2)
            print("FPS={}".format(clock.fps()))



except KeyboardInterrupt as e:
    print("用户停止: ", e)
except BaseException as e:
    print(f"异常: {e}")
finally:
    # 停止传感器运行
    if isinstance(sensor, Sensor):
        sensor.stop()
    # 反初始化显示模块
    Display.deinit()
    os.exitpoint(os.EXITPOINT_ENABLE_SLEEP)
    time.sleep_ms(100)
    # 释放媒体缓冲区
    MediaManager.deinit()
