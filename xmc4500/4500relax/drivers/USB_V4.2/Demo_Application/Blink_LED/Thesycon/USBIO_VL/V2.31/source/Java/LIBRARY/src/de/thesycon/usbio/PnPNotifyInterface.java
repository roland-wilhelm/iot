package de.thesycon.usbio;

/**
 * Interface for plug and play notifications.
 */
public interface PnPNotifyInterface
{
	/**
	 * Called if a device is added.
	 */
	public void onAdd();

	/**
	 * Called if a device is removed
	 */
	public void onRemove();
}