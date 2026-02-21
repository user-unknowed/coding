import turtle

# 设置画笔颜色为绿色，宽度为2
turtle.color("green")
turtle.pensize(2)

# 绘制三个同心圆
for radius in [30, 60, 90]:
    turtle.penup()              # 抬起画笔
    turtle.goto(0, -radius)     # 移动到圆心位置
    turtle.pendown()            # 放下画笔
    turtle.circle(radius)       # 绘制圆

turtle.done()  # 完成绘图
