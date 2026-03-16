package DroneRemoteUnit;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	DashboardView view;
	LogView logger;
	
	public MonitoringAgent(SerialCommChannel channel, DashboardView view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.channel = channel;
	}
	
	public void run(){
		boolean inMaintenance = false;
		boolean isFull = false;
		while (true){
			try {
				String msg = channel.receiveMsg();
				// logger.log("new msg: "+msg);				
				if (msg.startsWith(CONTAINER_PREFIX)){
					String cmd = msg.substring(CONTAINER_PREFIX.length()); 
					// logger.log("new command: "+cmd);				
					
					if (cmd.startsWith(MSG_STATE)){
						try {
							String args = cmd.substring(MSG_STATE.length()); 
							
							String[] elems = args.split(":");
							if (elems.length >= 3) {
								int stateCode = Integer.parseInt(elems[0]);
								int wasteLevel = Integer.parseInt(elems[1]);
								double temp = Double.parseDouble(elems[2]);
		
								view.setWasteLevel(wasteLevel);
								view.setCurrentTemperature(temp);
								view.setContainerState(stateNames[stateCode]);
								
								if (stateCode == IN_MAINTENANCE && !inMaintenance) { // maintenance
									inMaintenance = true;
									view.enableMaintenance();
								} else if (stateCode == FULL && !isFull) { // maintenance
									isFull = true;
									view.enableDischarge();
								} else if (stateCode == AVAILABLE && inMaintenance) {
									inMaintenance = false;
									view.enableAvailable();
								} else if (stateCode == AVAILABLE && isFull) {
									isFull = false;
									view.enableAvailable();
								}
								
							}
						} catch (Exception ex) {
							ex.printStackTrace();
							System.err.println("Error in msg: " + cmd);
						}
					}
				} else if (msg.startsWith(LOG_PREFIX)){
					this.logger.log(msg.substring(LOG_PREFIX.length()));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}
