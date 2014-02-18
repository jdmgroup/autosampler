import serial

class Autosampler:
	def __init__(self,comport):
		self.serialcon = serial.Serial('COM3',timeout=2)
		self.check()

	def advance(self):
		self.serialcon.write('2')
		resp = self.serialcon.read(7)
		
		if not resp.startswith('moved'):
			print('ERROR: Unexpected response from autosampler after advance')

	def valve(self,state):
		if state:
			self.serialcon.write('1')
			expect = 'on'
		else:
			self.serialcon.write('0')
			expect = 'off'

		resp = self.serialcon.read(len(expect)+2)
		if not resp.startswith(expect):
			print('ERROR: Unexpected response from autosampler after valve')


	def check(self):
		self.serialcon.write('?')
		expect = 'ready'
		resp = self.serialcon.read(len(expect)+2)
		
		if not resp.startswith(expect):
			print('ERROR: nexpected response from autosampler with check')