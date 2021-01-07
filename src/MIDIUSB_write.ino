/*
 * MIDIUSB_test.ino
 *
 * Created: 4/6/2015 10:47:08 AM
 * Author: gurbrinder grewal
 * Modified by Arduino LLC (2015)
 */ 

#include "MIDIUSB.h"

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void setup()
{
  Serial.begin(115200);
  MidiUSB.flush();
}

void loop()
{
	int16_t ad_value;
	int32_t strength=0;
	int16_t inhibit=128;
	int16_t remain;

	do
	{
		ad_value=analogRead(A1);
		delayMicroseconds(64);
	} while (ad_value<=10);
	
	remain=inhibit;
	do
	{
		strength+=ad_value;
		ad_value=analogRead(A1);
		delayMicroseconds(64);
		if (ad_value>10)
		{
			remain=inhibit;
		}
		remain--;
	} while (remain);

	Serial.println(strength);
	int16_t velo=8;
	while(strength)
	{
		strength>>=1;
		velo+=4;
	}
	if (velo>127)
	{
		velo=127;
	}
	Serial.println(velo);

  //Serial.println("Sending note on");
  noteOn(9, 39, velo);   // Channel 0, middle C, normal velocity
  //controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
  MidiUSB.flush();
  //delay(500);
  //Serial.println("Sending note off");
  //noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
  //MidiUSB.flush();
  //delay(1500);

}
