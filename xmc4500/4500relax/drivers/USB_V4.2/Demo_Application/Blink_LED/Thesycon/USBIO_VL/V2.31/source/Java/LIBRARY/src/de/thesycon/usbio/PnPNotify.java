package de.thesycon.usbio;

/**
 * Class for register plug and play notifications for a guid.
 */
public class PnPNotify implements PnPNotifyInterface, UsbIoErrorCodes
{
	private PnPNotifyInterface interf;

	/**
	 * Disable plug and play notifications for a guid.
	 */
	public native int disablePnPNotification(String guid);

	private native int enablePnPNotification(String guid, PnPNotifyInterface Interface);

	// load dll

	static {
		System.loadLibrary("USBIOJAVA");
	}

	/**
	 * Standard constructor of the PnPNotify class.
	 */
	public PnPNotify () {
		interf = null;
	}

	/**
	 * Constructor of the PnPNotify class.
	 *
	 * @param Interface Reference to a PnPNotifyInterface object.
	 */
	public PnPNotify (PnPNotifyInterface Interface) {
		interf = Interface;
	}

	/**
	 * Enable plug and play notifications for a guid.
	 */
	public int enablePnPNotification(String guid) {
		if (guid == null) {
			return USBIO_ERR_FAILED;
		}
		if (interf == null) {
			return enablePnPNotification(guid,this);
		} else {
			return enablePnPNotification(guid,interf);
		}
	}

	/**
	 * Called if a device is added.
	 */
	public void onAdd() {
	}

	/**
	 * Called if a device is removed
	 */
	public void onRemove() {
	}
}