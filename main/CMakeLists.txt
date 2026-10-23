idf_component_register(SRCS "main.c"
                       PRIV_REQUIRES leds spi_flash dht_sensor display pir_sensor obstacles_sensor
                       INCLUDE_DIRS "")
