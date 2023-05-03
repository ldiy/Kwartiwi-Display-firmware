idf_component_register(
        SRCS "main.c" "networking.c" "buzzer.c"  "ui_task.c" "tsc2046.c" "ui/ui.c" "ui/tp_cal_screen.c" "ui/img/tp_cal_cross_img.c"
        INCLUDE_DIRS "." "include" "ui/include"
)