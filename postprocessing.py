import ROOT
import sys, os, subprocess
from math import sqrt

di="kfactors_shape"    
bins = ["200_500","500_1000","1500_5000"]
#uncerts = ["","_Renorm_Up","_Renorm_Down","_Fact_Up","_Fact_Down","_PDF_Up","_PDF_Down"]
uncerts = ["","_Renorm_Up","_Renorm_Down","_Fact_Up","_Fact_Down"]
cols = [1,2,4]
cols = cols[:len(bins)]
base = "kfactor_vbf_mjj_"

def main():
    filenames = ["VBF_wjet","VBF_zjet"]

    for fn in filenames:
        fin = ROOT.TFile.Open("plots/"+sys.argv[1]+"/kfactor_" + fn + ".root","UPDATE")
        allh_fit = []
        allh = []
        allf = []
        #histtype = "_fit"
        histtype = ""

        for uncert in uncerts:
            temp = []
            tempf = []
            temp_fit = []
            for i,c in enumerate(cols): 
                h = fin.Get("%s%s/%s%s%s"%(di,uncert,base,bins[i],""))
                temp.append(h)
                if ( uncert == "" ):
                    h_fit = fin.Get("%s%s/%s%s%s"%(di,uncert,base,bins[i],"_fit"))
                    f = fin.Get("%s%s/%s%s%s"%(di,uncert,base,bins[i],"_fitfunc"))
                    temp_fit.append(h_fit)
                    allf.append(f)

            allh.append(temp)

            if ( uncert == "" ):
                allh_fit.append(temp_fit)

#        calculateUncertainty(allh)
        appendFittedUncertaintyToFile(allh,allh_fit,allf,fin)

    reTar()

def reTar():

    cmd = "cd plots;rm "+ sys.argv[1] + ".tar.gz; tar -zcf " + sys.argv[1] + ".tar.gz " + sys.argv[1] + ";  cd ../plots"
    subprocess.call( cmd, shell=True );



def calculateUncertainty(lists):

    scaleup = []
    pdfup = []
    totalup = []
    scaledown = []
    pdfdown = []
    totaldown = []

    
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
        

#def getUncertaintyRatios(hists,region,maxi=7):
def getUncertaintyRatios(hists,region,maxi=5):

    default = list(zip(*hists))[region]
    ratios = []

    for i in range (maxi):
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
    
  
def appendFittedUncertaintyToFile(hists,hists_fit,funcs,filein):
 
        
        


    for i,uncert in enumerate(bins):
        ratios = getUncertaintyRatios(hists,i)
        ratios_fit = getUncertaintyRatios(hists_fit,i,1)
        pol1 = ROOT.TF1("pol1","pol1",170,470)
        for j,hist in enumerate(ratios):
            if (j==0): continue
            hist.Fit(pol1,"LRQ0")
            for b in range(1,hist.GetNbinsX()+1):
                hist.SetBinContent(b,pol1.Eval(hist.GetBinCenter(b)))
            hist.Multiply(ratios_fit[0])
            #            func[i]*pol1


            def multiplyFunc(x):
                val = funcs[i].Eval(x[0])*pol1.Eval(x[0])
                return val 
 
            funcMultiplied = ROOT.TF1("funcMultiplied",multiplyFunc,0,1050)

            filein.cd("kfactors_shape" + uncerts[j])
            hist.Write( base + uncert + "_fit")
            funcMultiplied.Write( base + uncert + "_fitfunc")
            filein.cd("..")
  
        

#Run file
main()
