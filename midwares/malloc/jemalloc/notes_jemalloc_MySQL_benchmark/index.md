[MySQL性能测试--jemalloc内存管理](http://blog.chinaunix.net/uid-26896862-id-3865087.html)

分类： Mysql/postgreSQL

2013-08-26 01:06:09

# **1.****目的**

测试在jemalloc内存管理方式与glibc库的malloc内存管理方式两种情况下，MySQL的性能情况。通过测试，希望能够从内存管理方式的优化上，提高MySQL的性能。

## 2.测试环境

### 2.1 测试服务器硬件环境

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="568" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>Summary:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Dell R720xd, 2 x Xeon E5-2630 0 2.30GHz, 189GB / 192GB 1333MHz DDR3</span></p><p style="text-indent:0cm;"><span>System:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Dell PowerEdge R720xd (Dell 0X6FFV)</span></p><p style="text-indent:0cm;"><span>Processors:&nbsp;&nbsp;&nbsp;&nbsp; 2 x Xeon E5-2630 0 2.30GHz 7200MHz FSB (HT enabled, 12 cores, 24 threads)</span></p><p style="text-indent:0cm;"><span>Memory:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 189GB / 192GB 1333MHz DDR3 == 12 x 16GB - 16GB PC3-10600 Hynix DDR3-1333 ECC Registered CL9 2Rx4</span></p></td></tr></tbody></table>

### 2.2测试服务器软件环境

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="568" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>Linux 2.6.32-220.23.2.ali878.el6.x86_64</span></p><p style="text-indent:0cm;"><span>mysql-5.5.18</span></p></td></tr></tbody></table>

### 2.3 MySQL配置

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="568" valign="top" style="border:solid windowtext 1.0pt;"><p align="left" style="text-indent:0cm;"><span>binlog_format[ROW]</span></p><p align="left" style="text-indent:0cm;"><span>max_binlog_cache_size[2G]</span></p><p align="left" style="text-indent:0cm;"><span>max_binlog_size[500M]</span></p><p align="left" style="text-indent:0cm;"><span>sync_binlog[1]</span></p><p align="left" style="text-indent:0cm;"><span>thread_cache_size[256]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_buffer_pool_instances[8]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_buffer_pool_size[74G]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_flush_log_at_trx_commit[1]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_flush_method[O_DIRECT]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_io_capacity[1000]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_log_buffer_size[64M]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_log_file_size[1G]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_log_files_in_group[4]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_max_dirty_pages_pct[60]</span></p><p align="left" style="text-indent:0cm;"><span>innodb_thread_concurrency[16]</span></p></td></tr></tbody></table>

## 3.测试方案

### 3.1测试内容

测试glibc库的malloc与jemalloc的内存管理方式，分别在只读模式和读写混合模式下，随着测试连接线程数的增多，MySQL性能的影响，以及内存的使用情况。

### 3.2测试连接线程数

<table border="1" cellspacing="0" cellpadding="0" width="87%" style="width:87.3%;border:none;"><tbody><tr><td width="27%" valign="top" style="border:solid #4F81BD 2.25pt;"><p style="text-indent:0cm;"><b><span>Connect thread</span></b></p></td><td width="14%" valign="top" style="border:solid #4F81BD 2.25pt;"><p align="center" style="text-align:center;text-indent:0cm;"><span>32</span></p></td><td width="14%" valign="top" style="border:solid #4F81BD 2.25pt;"><p align="center" style="text-align:center;text-indent:0cm;"><span>64</span></p></td><td width="14%" valign="top" style="border:solid #4F81BD 2.25pt;"><p align="center" style="text-align:center;text-indent:0cm;"><span>128</span></p></td><td width="14%" valign="top" style="border:solid #4F81BD 2.25pt;"><p align="center" style="text-align:center;text-indent:0cm;"><span>256</span></p></td><td width="14%" valign="top" style="border:solid #4F81BD 2.25pt;"><p align="center" style="text-align:center;text-indent:0cm;"><span>512</span></p></td></tr></tbody></table>

### 3.3测试内存管理版本

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="114" valign="top" style="border:solid #4F81BD 2.25pt;"><p style="text-indent:0cm;"><b><span>Version</span></b></p></td><td width="114" valign="top" style="border:solid #4F81BD 2.25pt;"><p style="text-indent:0cm;"><span>glibc-2.12</span></p></td><td width="114" valign="top" style="border:solid #4F81BD 2.25pt;"><p style="text-indent:0cm;"><span>jemalloc-3.4.0</span></p></td></tr></tbody></table>

### 3.4测试指令

测试通过sysbench压测工具进行压力测试，数据量（约为23G）小于innodb\_buffer\_pool\_size的大小，使得IO不成为瓶颈。通过只读和读写混合测试，测试MySQL的性能。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="568" valign="top" style="border:solid windowtext 1.0pt;"><p align="left" style="text-indent:0cm;"><span style="font-size:9pt;"># </span><span style="font-size:9pt;font-family:宋体;">初始化数据</span><span style="font-size:9pt;"></span></p><p align="left" style="text-indent:0cm;"><span style="font-size:9pt;">./sysbench --test=tests/db/parallel_prepare.lua --max-time=1000 --oltp-dist-type=uniform --max-requests=0 --mysql-user=test --mysql-password=test --mysql-table-engine=innodb --oltp-table-size=3000000 --oltp-tables-count=32 --oltp-range-size=90 --oltp-point-selects=1 --oltp-simple-ranges=1 --oltp-sum-ranHges=1 --oltp-order-ranges=1 --oltp-distinct-ranges=1 --oltp-non-index-updates=10 --num-threads=32&nbsp; --mysql-host=10.207.105.1 --mysql-port=3306 run</span></p><p align="left" style="text-indent:0cm;"><span style="font-size:9pt;"># </span><span style="font-size:9pt;font-family:宋体;">只读</span><span style="font-size:9pt;font-family:宋体;">压力测试</span><span style="font-size:9pt;"></span></p><p align="left" style="text-indent:0cm;"><span style="font-size:9pt;">./sysbench --test=tests/db/oltp.lua --max-time=3600 --oltp-dist-type=uniform --max-requests=0 --mysql-user=test --mysql-password=test --mysql-table-engi ne=innodb --oltp-table-size=3000000 --oltp-tables-count=</span><span style="font-size:9.0pt;color:red;">32</span><span style="font-size:9pt;"> --oltp-range-size=90 --oltp-point-selects=12 --num-threads=64 --mysql-host=10.207.105.1 --my sql-port=3306&nbsp; --oltp-read-only=on run</span></p><p align="left" style="text-indent:0cm;"><span style="font-size:9pt;"># </span><span style="font-size:9pt;font-family:宋体;">读写混合压力测试</span><span style="font-size:9pt;"></span></p><p align="left" style="text-indent:0cm;"><span style="font-size:9.0pt;">./sysbench --test=tests/db/oltp.lua --max-time=3600 --oltp-dist-type=uniform --max-requests=0 --mysql-user=test --mysql-password=test --mysql-table-engine=innodb --oltp-table-size=3000000 --oltp-tables-count=32 --oltp-range-size=90 --oltp-point-selects=12 --oltp-index-updates=1 --oltp-non-index-updates=1 --num-threads=<span style="color:red;">32</span> --mysql-host=10.207.105.1 --mysql-port=3306 run</span></p></td></tr></tbody></table>

## 4.性能指标

性能指标主要包括：

 cpu： %user

 memory：vsize，rss

 mysql：QPS，TPS

其中，vsize表示mysqld进程的虚拟地址空间大小；rss表示驻留物理地址空间的大小。查看原因见参考文档。

## 5.测试结果

### 5.1只读测试

**1****、CPU****利用率**

 MySQL在只读测试下，随着线程数的增加，CPU的%usr的变化。从测试结果来看，jemalloc内存分配方式与glibc的malloc相比，CPU的利用率降低，并且利用率随线程数的增加而差距增大。但是当线程数到达512时，CPU利用率基本一致，分析原因是由于达到CPU的处理上线导致。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-0ed38a8a5a153d0127c1688f0b0321e3.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-b9b117879a715138b0041209853cdfde.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>1.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">只读模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>1.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">只读模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-1be2d6e9d3bed82333e0c5482a65f5f8.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-d91867b73f3607570eae3d5c32e1d36c.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>1.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">只读模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>1.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">只读模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-848ff424afe703d5ad66426761efeb74.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-1aa16c6d7100c59dcbcf88b0c6af2633.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>1.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">只读模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>1.6 CPU %user</span><span style="font-family:宋体;">利用率随线程数的变化</span></p></td></tr></tbody></table>

**2****、QPS**

 MySQL只读测试下，jemalloc内存分配方式比glic的malloc方式，QPS有较大的提高，并且提高程度随线程数增加而幅度加大。具体如下所示：

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-a47925120f8ecc03485cf90261e26d4e.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-8d611345a1fc9e4327cc7d60f8fb3b2b.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>2.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">只读模式的</span><span>QPS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>2.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">只读模式的</span><span>QPS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-0b6d7f1047cb675880d867305c96e09a.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-95d0a9d14f1587af47642b0541e5784f.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>2.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">只读模式的</span><span>QPS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>2.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">只读模式的</span><span>QPS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-95ad830a65a6a6f19d07a7ddb9f54f22.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><br></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-a5f81e3a4830224ac9740be99c404dfb.png" width="483" height="291" alt="" style="white-space:normal;"><span style="text-indent:0cm;line-height:1.5;"></span></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>2.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">只读模式的</span><span>QPS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>2.6 QPS</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

**3****、MySQL****的RSS**

 MySQL只读测试下，随着线程数的增加，MySQL的RSS在jemalloc内存方式下比glic的malloc方式下，占用物理内存的大小差距越来越大。具体如下图所示：

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-157b2134a4eaf5fee62a1fe1e8b5e99b.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-c8135f590b68da316da9198f2207d89a.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>3.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">只读模式的</span><span>RSS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>3.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">只读模式的</span><span>RSS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-31f62844952f264644d3243ad2b21b07.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-bf8b3eb378216433540f8629d347f8e0.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>3.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">只读模式的</span><span>RSS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>3.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">只读模式的</span><span>RSS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-8c28ea1953973045d873345b2cdd2101.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-6aede8753f140443addb43b9138e959f.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>3.5 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">只读模式的</span><span>RSS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>3.6 RSS</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

**4****、MySQL****的VSIZE**

 MySQL只读测试下，jemalloc内存方式与glic的malloc方式相比，MySQL的VSIZE的大小减小了较多，并且随着线程数的增大，差距越来越大。具体如下图所示：

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-349bf3980d016ef509e340e9ee6e652d.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-5b597ccae6c20bcc044e5a38fd4705d9.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>4.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">只读模式的</span><span>VSIZE</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>4.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">只读模式的</span><span>VSIZE</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-60da91be6bc6ec8b08fb72745e820c16.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-e484248d4c4d45dc9a88a9883540d294.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>4.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">只读模式的</span><span>VSIZE</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>4.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">只读模式的</span><span>VSIZE</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-05a755190a4bdce76bd2205c37d26853.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-0695edfad73efb3a976baa15b5d1e655.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>4.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">只读模式的</span><span>VSIZE</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>4.6 VSIZE</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

### 5.2读写测试

**1****、CPU****利用率**

 MySQL在读写混合模式下（读写比6:1），随着线程数的增加，jemalloc内存分配方式与glic的malloc分配方式相比，CPU的%user利用率无明显变化。从以下结果中可知，在读写混合模式下，MySQL对CPU的利用很快达到瓶颈，线程数的增加没有明显效果。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-0e4c11d5804805a1efea0b22939df18f.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-7a5a7d850ed90594138ce71cbdec5dc9.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>5.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">读写模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>5.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">读写模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-fcc81749829d04bac3d00c02e4c38482.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-6b0b1815a85b79f1d6e2873e5aa8e586.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>5.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">读写模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>5.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">读写模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-d292e346bd9af2d147a40abf95bdacaf.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-ba6e4a2d3a0347e979247f2d907289d0.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>5.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">读写模式的</span><span>%user</span><span style="font-family:宋体;">利用率</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>5.6 CPU %user</span><span style="font-family:宋体;">利用率随线程数的变化</span></p></td></tr></tbody></table>

**2****、QPS**

 在读写混合模式下，MySQL的QPS随着线程数的增加，有一些提高，但与只读模式测试相比，提高幅度较小。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-a3978e0ff12004c43e8a7886a26a1abe.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-2dbd64a45cd7b6e44afa7010939c63aa.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>6.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">读写模式的</span><span>QPS&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>6.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">读写模式的</span><span>QPS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-644ca25d304848525228b1bcfa9436d3.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-1b6f7fdafefcb22ae4f5df1eb0828209.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>6.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">读写模式的</span><span>QPS&nbsp;&nbsp;&nbsp;&nbsp;</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>6.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">读写模式的</span><span>QPS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-245983a8be3e3d35a2e1d49bcce667a5.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-d86af6e1b711f72508bc1d0f8aa2d8e3.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>6.5 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">读写模式的</span><span>QPS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>6.6 QPS</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

**3****、TPS**

 在读写混合模式下，MySQL的TPS随着线程数的增加，jemalloc内存分配方式与glic的malloc相比，提高程度不断增大。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-a70133376a8e300eab2af3a9145a4cb4.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-91f224d123374e3158577669362b8fed.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>7.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">读写模式的</span><span>TPS&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>7.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">读写模式的</span><span>TPS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-c13e9e8937e45bea4a96356e0cffe22e.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-85608cdaaa4990a5ffe83102ff429ae5.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>7.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">读写模式的</span><span>TPS&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>7.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">读写模式的</span><span>TPS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-35cc240a872d8fd1ba0621d30b815b2e.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-a1e22c78c1ad8c3cf4fe9d175debc4bd.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>7.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">读写模式的</span><span>TPS&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>7.6 TPS</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

**4****、RSS**

 在读写混合模式下，随着线程数的增加，jemalloc内存分配方式与glic的malloc相比，MySQL的RSS不断减小。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-780b7fd79375453b3d0774819fb8ee11.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-4f4a80db114674a77f8bcf16c3070104.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>8.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">读写模式的</span><span>RSS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>8.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">读写模式的</span><span>RSS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-92bdb227f1246ed1af1fcfb4e3964364.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-beb66881098883c0f6ced9500649b43d.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>8.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">读写模式的</span><span>RSS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>8.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">读写模式的</span><span>RSS</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-bd514c0b49915cf0540465e141589636.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-2175e64482ed7ce5bf48cf694a52d27a.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>8.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">读写模式的</span><span>RSS</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>8.6 RSS</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

**5****、VSIZE**

 在读写混合模式下，随着线程数的增加，jemalloc内存分配方式与glic的malloc相比，MySQL的VSIZE大小差距不断增加。

<table border="1" cellspacing="0" cellpadding="0" style="border:none;"><tbody><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-962f6e2147817f38ffbf6b387e92ee80.png" width="483" height="291" alt=""><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-f8ba3f8a1d8c7e1dd51242006fc11e96.png" width="483" height="291" alt="" style="white-space:normal;"><span style="text-indent:0cm;line-height:1.5;"></span></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>9.1 </span><span style="font-family:宋体;">线程数</span><span>32</span><span style="font-family:宋体;">读写模式的</span><span>VSIZE</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>9.2 </span><span style="font-family:宋体;">线程数</span><span>64</span><span style="font-family:宋体;">读写模式的</span><span>VSIZE</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-0a1295193b2a3a117521b004db47862e.png" width="483" height="291" alt="" style="white-space:normal;"></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-699d795af1ad1ac2fae0f0aad5eeb18c.png" width="483" height="291" alt="" style="white-space:normal;"></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>9.3 </span><span style="font-family:宋体;">线程数</span><span>128</span><span style="font-family:宋体;">读写模式的</span><span>VSIZE</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>9.4 </span><span style="font-family:宋体;">线程数</span><span>256</span><span style="font-family:宋体;">读写模式的</span><span>VSIZE</span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-be5cd893732b8a25c96091aab365eb9e.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><img src="assets/1616378925-1cf168ad2232231638727fbdc157ccde.png" width="483" height="291" alt="" style="white-space:normal;"><p style="text-indent:0cm;"><span></span></p></td></tr><tr><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>9.5 </span><span style="font-family:宋体;">线程数</span><span>512</span><span style="font-family:宋体;">读写模式的</span><span>VSIZE</span></p></td><td width="284" valign="top" style="border:solid windowtext 1.0pt;"><p style="text-indent:0cm;"><span>9.6 VSIZE</span><span style="font-family:宋体;">随线程数的变化</span></p></td></tr></tbody></table>

## 6.结论

 通过测试，发现jemalloc内存分配方式与glic的malloc内存分配方式相比，在只读模式下，CPU利用率最大降低了10%左右；MySQL的RSS最大降低了12%左右；MySQL的VSIZE最大降低了1%左右；MySQL的QPS最大提高了25%左右。

 在读写混合模式下，CPU利用率基本无变化，是由于MySQL的CPU利用很快达到瓶颈的原因；MySQL的RSS最大降低了11%左右；MySQL的VSIZE最大降低了28%；MySQL的QPS最大提高了15%；MySQL的TPS最大提高了15%左右。

 整体来看，jemalloc内存分配方式与glic的malloc内存分配方式相比，提高了MySQL的性能，降低了系统CPU和内存资源的利用。从压测情况来看，基本达到测试的期望。

## 参考

\[1\].[http://www.mysqlperformanceblog.com/2012/07/05/impact-of-memory-allocators-on-mysql-performance/](http://www.mysqlperformanceblog.com/2012/07/05/impact-of-memory-allocators-on-mysql-performance/)

\[2\]. [http://www.mysqlperformanceblog.com/2013/03/08/mysql-performance-impact-of-memory-allocators-part-2/](http://www.mysqlperformanceblog.com/2013/03/08/mysql-performance-impact-of-memory-allocators-part-2/)

阅读(13922) | 评论(1) | 转发(2) |

0[](javascript:)

上一篇：[CGroup的BLKIO资源隔离--结论](http://blog.chinaunix.net/uid-26896862-id-3847079.html)

下一篇：[MySQL学习分享--机型选择与配置](http://blog.chinaunix.net/uid-26896862-id-3947862.html)