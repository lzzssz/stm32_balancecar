import time, os, sys
from media.sensor import *
from media.display import *
from media.media import *

sensor = None

try:

        sensor = Sensor()
        sensor.reset()

        sensor.set_framesize(width=1920,height=1080)
        sensor.set_pixformat(Sensor.RGB565)

        # 使用IDE的帧缓冲区作为显示输出
        Display.init(Display.LT9611, to_ide=True)
        # 初始化媒体管理器
        MediaManager.init()
        # 启动传感器
        sensor.run()

        while True:
            os.exitpoint()
            img = sensor.snapshot(chn=CAM_CHN_ID_0)
            img.draw_string_advanced(50,50,80,"不会K230",color=(255,0,0))
            img.draw_line(200,200,200,500,thickness=50,color=(0,255,0))
            img.draw_rectangle(500,300,700,600,thickness=20,color=(0,255,0))
            img.draw_keypoints([[500,500,160],[500,700,0]],thickness=10,color=(0,0,70),size=50)
            img.draw_circle(600,600,40,thickness=20,color=(0,255,0))
            Display.show_image(img)




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
