import ROOT
import sys, os
from math import sqrt
outdir = "plots/"+sys.argv[2]
if os.path.exists(outdir) == False:
    os.mkdir(outdir) 
fin = ROOT.TFile.Open(sys.argv[1],"UPDATE")
di="kfactors_shape"
bins = ["200_500","500_1000","1500_5000"]
uncerts = ["","_Renorm_Up","_Renorm_Down","_Fact_Up","_Fact_Down","_PDF_Up","_PDF_Down"]
cols = [1,2,4]
base = "kfactor_vbf_mjj_"
fcol=[ROOT.kGray,ROOT.kRed-9,ROOT.kAzure+6]

allh = []
scaleup = []
pdfup = []
totalup = []
scaledown = []
pdfdown = []
totaldown = []

def calculateUncertainty(lists):
    
    for i in range(len(bins)):
        uncert = list(zip(*lists))[i]
        scale_up = uncert[0].Clone()
        scale_down = uncert[0].Clone()
        total_up = uncert[0].Clone()
        total_down = uncert[0].Clone() 
        for b in range(uncert[0].GetNbinsX()+1):

            v_nom = uncert[0].GetBinContent(b)
            v_r_up = uncert[1].GetBinContent(b)
            v_r_down = uncert[2].GetBinContent(b)
            v_f_up = uncert[3].GetBinContent(b)
            v_f_down = uncert[4].GetBinContent(b)
            v_p_up = uncert[5].GetBinContent(b)
            v_p_down = uncert[6].GetBinContent(b)
            
            v_scale_down = sqrt( (v_r_up-v_nom)**2 + (v_f_up-v_nom)**2 )
            v_scale_up = sqrt( (v_r_down-v_nom)**2 + (v_f_down-v_nom)**2 )#down causes the k-factor to reduce, so swap arbitrary meaning

            v_total_up = sqrt( (v_p_up-v_nom)**2 + (v_scale_down)**2 )
            v_total_down = sqrt( (v_p_down-v_nom)**2 + (v_scale_up)**2 )
                          
            scale_up.SetBinContent( b, v_nom + v_scale_up )
            scale_down.SetBinContent( b, v_nom - v_scale_down )
            total_up.SetBinContent( b, v_nom + v_total_up )
            total_down.SetBinContent( b, v_nom - v_total_down )

        scaleup.append ( scale_up )
        scaledown.append ( scale_down )
        totalup.append ( total_up )
        totaldown.append ( total_down )

    lists.append(scaleup)
    lists.append(scaledown)
    lists.append(totalup)
    lists.append(totaldown)
        

def getUncertaintyRatios(hists,region):

    default = list(zip(*hists))[region]
    ratios = []

    for i in range (7):
        uncert = default[i].Clone("uncert"+str(i))
        if (i != 0):
            uncert.Divide(default[0])
        uncert.SetFillColor(0)
        colour = i;
        if ( colour == 5 ):
            colour = 9
        uncert.SetLineColor(colour)
        uncert.SetMarkerColor(colour)
        ratios.append(uncert)

    return ratios
    
  
def appendFittedUncertaintyToFile(hists):
    
    for i,uncert in enumerate(bins):
        ratios = getUncertaintyRatios(hists,i)
        pol2 = ROOT.TF1("pol2","pol1",170,470)
        for j,hist in enumerate(ratios):
            if (j==0): continue
            hist.Fit(pol2,"LRQ0")
            for b in range(2,hist.GetNbinsX()+1):
                hist.SetBinContent(b,pol2.Eval(hist.GetBinCenter(b)))
            hist.Multiply(ratios[0])
            fin.cd("kfactors_shape" + uncerts[j])
            hist.Write( base + uncert + "_fit6")
            fin.cd("..")
  
#histtype = "_fit"
histtype = ""
cols = cols[:len(bins)]
for uncert in uncerts:
    temp = []
    for i,c in enumerate(cols): 
        h = fin.Get("%s%s/%s%s%s"%(di,uncert,base,bins[i],histtype))
        temp.append(h)
    allh.append(temp)

calculateUncertainty(allh)
appendFittedUncertaintyToFile(allh)

