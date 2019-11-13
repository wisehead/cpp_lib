/*******************************************************************************
 *      File Name: foo.c                                               
 *         Author: Hui Chen. (c) 2019                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2019/11/13-19:22                                    
 *	Modified Time: 2019/11/13-19:22                                    
 *******************************************************************************/
#include <gflags/gflags.h>
#include <iostream>

DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(languages, "english,french,german", "comma-separated list of languages to offer in the 'lang' menu");

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  std::cout << "argc=" << argc << std::endl;
  if (FLAGS_big_menu) {
      std::cout << "big menu is ture" << std::endl;
  } else {
      std::cout << "big menu is flase" << std::endl;
  }

  std::cout << "languages=" << FLAGS_languages << std::endl;
  return 0;
}
