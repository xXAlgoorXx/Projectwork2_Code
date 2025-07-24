# STM32 ISP Library

![latest tag](https://img.shields.io/badge/tag-1.1.0-blue)

The ISP Library middleware (running on the target) hosts 2A algorithms
(Auto Exposure and Auto White Balance) and mechanisms to control the
ISP and load sensor ISP tuning file.

The STM32 ISP Library also implements a communication mechanism with the
STM32 ISP IQTune desktop application that provide services to tune the
ISP present in STM32 devices.
To activate this communication through USB link, the compilation flag
ISP_MW_TUNING_TOOL_SUPPORT must be enabled.

## Structure
- isp: core of the ISP Library with the ISP parameter configuration
- isp_param_conf: collection of sensor tuning parameters
- evision: 2A algorithms that are delivered as binary

## Enhancements, new features
- Add sensor delay feature that can be manually set or automaticaly computed thanks to the STM32-ISP-IQTune desktop application
- Improve AWB algorithm to avoid flickering between 2 illuminants
- Add AEC anti-flicker feature that support 50Hz and 60Hz region.
- Statistic area has been removed from init parameter of the ISP_Init() function
- Fix IAR build warnings in the evision libraries

## Known Issues and Limitations
- None

## STM32 ISP IQTune desktop application
<https://www.st.com/en/development-tools/stm32-isp-iqtune.html>

## STM32 ISP Wiki documentation
<https://wiki.st.com/stm32mcu/wiki/Category:ISP>

## STM32 ISP tuning procedure
<https://wiki.st.com/stm32mcu/wiki/ISP:How_to_tune_ISP_using_the_STM32_ISP_IQTune>
