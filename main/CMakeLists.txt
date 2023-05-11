idf_component_register(
        SRCS "main.c" "networking.c" "buzzer.c"  "ui_task.c" "tsc2046.c" "ui/ui.c" "ui/tp_cal_screen.c" "ui/img/tp_cal_cross_img.c" "web_client.c" "data_manager.c" "ui/img/kwartiwi_logo.c" "ui/loading_screen.c" "ui/main_screen.c"
        INCLUDE_DIRS "." "include" "ui/include"
)