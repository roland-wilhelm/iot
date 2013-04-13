using System;
using USBIOCOMLib;
using System.Threading;

namespace Thesycon
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class CSharpMouseSample
	{
		
		static USBIOInterface3Class Device;
		static ManualResetEvent ev;

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			int Devices;
			int Status;
			Thread th;

			// create event
			ev = new ManualResetEvent(false);

			// create thread for keyboard input
			th = new Thread(new ThreadStart(WaitForKey));
			th.Start();

			// create instance of USBIOCOM object
			Device = new USBIOInterface3Class();
			Device.ReadComplete += new _IUSBIOInterfaceEvents3_ReadCompleteEventHandler(Device_ReadComplete);

			// enumerate devices
			Device.EnumerateDevices("{325ddf96-938c-11d3-9e34-0080c82727f4}",out Devices);

			// check if a device was found
			if (Devices>0)
			{
				// open first device
				Device.OpenDevice(0,out Status);
				if (Status == (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("USB device opened");
				} 
				else 
				{
					System.Console.WriteLine("Cannot open the USB device");
				}
				// add interface
				Device.AddInterface(0,0,4096,out Status);
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error AddInterface {0}",Status);
				}
				// set configuration
				Device.SetConfiguration(0,out Status);
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error SetConfiguration {0}",Status);
				}
				// bind pipe
				Device.Bind(0x81,out Status);
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error Bind {0}",Status);
				}
				// start reading from device device
				Device.StartReading(3,2,5,out Status);
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error StartReading {0}",Status);
				}
				// write to console
				System.Console.WriteLine("Press Enter to exit!");
				// wait for enter or mouse buttons
				ev.WaitOne();
				// stop reading
				Device.StopReading();
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error StopReading {0}",Status);
				}
				// unbind pipe
				Device.Unbind(out Status);
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error Unbind {0}",Status);
				}
				// unconfigure device
				Device.UnconfigureDevice(out Status);
				if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)
				{
					System.Console.WriteLine("Error UnconfigureDevice {0}",Status);
				}
				// close device
				Device.CloseDevice();
			}
			else 
			{
				System.Console.WriteLine("No USB device connected or USBIO device driver not installed");
			}
		}

		private static void WaitForKey() 
		{
			// read from console
			System.Console.ReadLine();
			ev.Set();
		}

		private static void Device_ReadComplete(object Obj)
		{
			int Status;
			int Count = 3;
			System.Array Buf;

			// create an array of bytes
			Buf = System.Array.CreateInstance(typeof(byte),3);

			// read from device
			Device.ReadData(ref Buf,out Count,out Status);
			if (Status != (int)USBIOCOM_ERR_CODES.USBIO_ERR_SUCCESS)  
			{
				System.Console.WriteLine("Error ReadData {0}",Status);
			}

			// write date to console
			System.Console.WriteLine("{0,3} {1,3} {2,3}",Buf.GetValue(0),Buf.GetValue(1),Buf.GetValue(2));
		}
	}
}
