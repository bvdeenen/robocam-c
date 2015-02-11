#!/usr/bin/python
# vim:ts=4:

import commands

class exec_error(Exception):
	def __init__(self,errnum,result):
		self.errnum = errnum
		self.result = result
	def __str__(self):
		return "err "+str(self.errnum)+": "+"\n".join(self.result)

def execute(cmd, log=0):
	(exitstatus,outtext)=commands.getstatusoutput(cmd)
	outtext=outtext.split("\n")
	if exitstatus!=0 or log:
		for line in outtext: print line
		
	if exitstatus : 
		raise exec_error(exitstatus, outtext)

	return (exitstatus, outtext)

(status, outtext)=execute("ps x| grep kst | grep -v grep")
fields= outtext[0].split()
pid=fields[0]
dcop_cmd="dcop kst-%s KstIface reloadVectors" % pid

N=64000

for noise in [0.5, 1, 2, 5, 10]:
	for i in range(10):
		cmd="./noise %g %d" % (noise,N)
		
		planned_peak=float((execute(cmd)[1])[0])

		cmd="./corr %d" % (N,)

		measured_peak=float((execute(cmd)[1])[0])
		execute(dcop_cmd)
		diff=(measured_peak-planned_peak)/36
		print noise, planned_peak, measured_peak, diff
		execute("sleep 1")


