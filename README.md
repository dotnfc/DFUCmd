# DFUCmd
An usb dfu util based on STMicroelectronics DfuSe v3.0.5

# Note
> 1. This repo has only one output: DFUCmd.exe (Win32) without any STM official DLLs.

> 2. Project file is for VC2015

# Command Help
```bash
DfuSe command line v1.0.0

 Usage :

 DfuSeCommand.exe [options] [Agrument][[options] [Agrument]...]

  -?                   (Show this help)
  -c                   (Connect to a DFU device )
     --de  device      : Number of the device target, by default 0
     --al  target      : Number of the alternate target, by default 0
  -u                   (Upload flash contents to a .dfu file )
     --fn  file_name   : full path name of the file
  -d                   (Download the content of a file into MCU flash)
     --v               : verify after download
     --o               : optimize; removes FFs data
     --fn  file_name   : full path name (.dfu file)
  -t                   (Convert hex file to dfu file )
  -e                   (Extract dfu file to hex file )
     --fn  file_name   : the source .dfu file full path
     --o   output_dir  : the target .hex file path to output

  eg: DfuSeCommand.exe -t --i test.hex -c --de 0 -d --fn test.dfu
      DfuSeCommand.exe -t D:\temp\ d:\sample.dfu
      DfuSeCommand.exe -e --fn D:\sample.dfu --o c:\
 
```

by dotnfc@163.com, 2018/09/01
