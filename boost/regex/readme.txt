2.regex_replace(string s, regex e, string t)，把s中匹配了e的子串替换为t

    regex reg("(colo)(u)(r)",boost::regex::icase|boost::regex::perl);
	  string s="Colour,colour,color,colOurize";
	    s=regex_replace(s,reg,"$1$3");

		t中的n代表reg中的第n个括号里的内容，3表示r，$1表示colo。上段代码表示把colour换成color，boost::regex::icase/boost::regex::perl是标志开关，表示忽略大小写。可以把需要的标志开关打开，不需要时默认关闭。
