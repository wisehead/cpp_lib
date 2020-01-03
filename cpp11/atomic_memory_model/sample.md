1.A sample in MySQL

	Define:
	 /** At a shutdown this value climbs from SRV_SHUTDOWN_NONE to
	 SRV_SHUTDOWN_CLEANUP and then to SRV_SHUTDOWN_LAST_PHASE, and so on */
	 std::atomic<enum srv_shutdown_t> srv_shutdown_state{SRV_SHUTDOWN_NONE};  
 
	write:
	srv_shutdown_state.store(SRV_SHUTDOWN_EXIT_THREADS);
	
	read:
	ut_ad(srv_shutdown_state.load() == SRV_SHUTDOWN_CLEANUP);