package ipResolver;

/**
 * This class stores all the methods/data
 * for an IPAddress.
 * @author cwixom (masc0582)
 */
public class IPAddress implements Comparable<IPAddress>{

	/**
	 * The IPAddress for the DNS Name.
	 */
	private String _ipAddress;
	
	private static final String PERIOD_REGEX = "\\.";
	private static final int MAX_SINGLE_IP_OCTET = 255;
	
	/**
	 * The constructor for an IPAddress
	 * @param ipAddress The IP Address string. The string must
	 * be a valid ip address [0-255]...etc.
	 * @exception NullPointerException For null argument.
	 * @exception IllegalArgumentException For empty string
	 * arguments or invalid IP Addresses.
	 */
	public IPAddress(
		String ipAddress){
		validateString(ipAddress, "IPAddress");
		validateIPAddress(ipAddress);
		_ipAddress = ipAddress;
	}

	/**
	 * @inheritDoc
	 */
	@Override
	public int compareTo(IPAddress arg0) {
		if(null == arg0){return -1;}
		
		return _ipAddress.compareTo(arg0._ipAddress);
	}
	
	/**
	 * @inheritDoc
	 */
	@Override
	public boolean equals(Object obj){
		if(null == obj){return false;}
		if(false == (obj instanceof IPAddress)){return false;}
		
		return compareTo((IPAddress)obj) == 0;
	}
	
	/**
	 * @inheritDoc
	 */
	@Override
	public int hashCode(){
		// As much as I'd like to think I 
		// could write a better hash code than
		// the java creators. I doubt it.
		// I'll just return the string IPAddress hash.
		return _ipAddress.hashCode();
	}
	
	/**
	 * Validates the string is not null or empty.
	 * @param stringToValidate
	 * @param nameOfString
	 */
	private void validateString(
			String stringToValidate,
			String nameOfString){
		if(null == stringToValidate){
			throw new NullPointerException(
				nameOfString + " was passed NULL.");
		}
		if(stringToValidate.equals("")){
			throw new IllegalArgumentException(
				nameOfString + " was passed EMPTY.");
		}
	}
	
	/**
	 * Validates an IP Address is valid.
	 * @param ipAddress
	 */
	private void validateIPAddress(String ipAddress){
		String[] ipOctets = ipAddress.split(PERIOD_REGEX);
		
		for(String octet : ipOctets){
			Integer intPart = tryParse(octet);
			if(null == intPart){
				throw new IllegalArgumentException(
						"Invalid IP. One of the " +
					    "octets is not an INT. " + 
					    "IP Address: " + ipAddress);
			}
			
			if(intPart < 0 || intPart > MAX_SINGLE_IP_OCTET){
				throw new IllegalArgumentException(
						"Invalid IP. One of the " +
					    "octets is not > 0 or <= " + MAX_SINGLE_IP_OCTET + 
					    " IP Address: " + ipAddress);
			}
		}
	}
	
	/**
	 * Tries to parse the string.
	 * @param parse
	 * @return
	 */
	public Integer tryParse(String string) {
		  try {return new Integer(string);} 
		  catch (NumberFormatException exception) {return null;}
		}
	
	/**
	 * @inheritDoc
	 */
	@Override
	public String toString(){
		return _ipAddress; 
	}
}