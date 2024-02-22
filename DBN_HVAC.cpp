// DBN_HVAC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include "smile.h"
#include "smile_license.h" 

static int CreateCptNode(
    DSL_network& net, const char* id, const char* name,
    std::initializer_list<const char*> outcomes, int xPos, int yPos);

static void UpdateAndShowTemporalResults(DSL_network& net);
//static void PrintAllPosteriors(DSL_network& net);


int main()
{
    printf("Starting FDD...\n");

    DSL_errorH().RedirectToFile(stdout);

    DSL_network net;
    //load Bayesian network
    int resn = net.ReadFile("Physical_based_DBN_HVAC_simplified_growF_twosteps_R1.xdsl");
    if (DSL_OKAY != resn)
    {
        printf(
            "Network load failed,\n");
        return resn;
    }


    //load building FDD dataset
    DSL_dataset ds;
    int resd = ds.ReadFile("R1_validation_cor.csv");
    if (DSL_OKAY != resd)
    {
        printf("Dataset load failed\n");
        return resd;
    }
    printf("Dataset has %d variables (columns) and %d records (rows)\n", ds.GetNumberOfVariables(), ds.GetNumberOfRecords());

    // check BN nodes
    int T_z_sensor = net.FindNode("T_z_sensor");
    if (T_z_sensor < 0)
    {
        printf("T_z_sensor node not found.");
        return T_z_sensor;
    }
    int T_rw_sensor = net.FindNode("T_rw_sensor");
    if (T_rw_sensor < 0)
    {
        printf("T_rw_sensor node not found.");
        return T_rw_sensor;
    }
    int T_sa_sensor = net.FindNode("T_sa_sensor");
    if (T_sa_sensor < 0)
    {
        printf("T_sa_sensor node not found.");
        return T_sa_sensor;
    }
    int m_sa_sensor = net.FindNode("m_sa_sensor");
    if (m_sa_sensor < 0)
    {
        printf("m_sa_sensor node not found.");
        return m_sa_sensor;
    }
    int m_sw_sensor = net.FindNode("m_sw_sensor");
    if (m_sw_sensor < 0)
    {
        printf("m_sw_sensor node not found.");
        return m_sw_sensor;
    }
    int T_sw_sensor = net.FindNode("T_sw_sensor");
    if (T_sw_sensor < 0)
    {
        printf("T_sw_sensor node not found.");
        return T_sw_sensor;
    }
    int T_o_sensor = net.FindNode("T_o_sensor");
    if (T_o_sensor < 0)
    {
        printf("T_o_sensor node not found.");
        return T_o_sensor;
    }

    int m_sw = net.FindNode("m_sw");
    if (m_sw < 0)
    {
        printf("m_sw node not found.");
        return m_sw;
    }
    int T_sw = net.FindNode("T_sw");
    if (T_sw < 0)
    {
        printf("T_sw node not found.");
        return T_sw;
    }
    int m_sa = net.FindNode("m_sa");
    if (m_sa < 0)
    {
        printf("m_sa node not found.");
        return m_sa;
    }
    int T_o = net.FindNode("T_o");
    if (T_o < 0)
    {
        printf("T_o node not found.");
        return T_o;
    }
    int Q_rad = net.FindNode("Q_rad");
    if (Q_rad < 0)
    {
        printf("Q_rad node not found.");
        return Q_rad;
    }
    int Q_ig = net.FindNode("Q_ig");
    if (Q_ig < 0)
    {
        printf("Q_ig node not found.");
        return Q_ig;
    }

    int T_z_sensor_cali = net.FindNode("T_z_recently_calibrated_");
    if (T_z_sensor_cali < 0)
    {
        printf("T_z_recently_calibrated node not found.");
        return T_z_sensor_cali;
    }
    int T_rw_sensor_cali = net.FindNode("T_rw_recently_calibrated_");
    if (T_rw_sensor_cali < 0)
    {
        printf("T_rw_recently_calibrated node not found.");
        return T_rw_sensor_cali;
    }
    int T_sa_sensor_cali = net.FindNode("T_sa_recently_calibrated_");
    if (T_sa_sensor_cali < 0)
    {
        printf("T_sa_recently_calibrated not found.");
        return T_sa_sensor_cali;
    }

    //check BN anchor nodes
    int T_z_i = net.FindNode("T_z_i");
    if (T_z_i < 0)
    {
        printf("T_z_i node not found.");
        return T_z_i;
    }
    int T_w_i = net.FindNode("T_w_i");
    if (T_w_i < 0)
    {
        printf("T_w_i node not found.");
        return T_w_i;
    }
    int T_rw_i = net.FindNode("T_rw_i");
    if (T_rw_i < 0)
    {
        printf("T_rw_i node not found.");
        return T_rw_i;
    }
    int T_sa_i = net.FindNode("T_sa_i");
    if (T_sa_i < 0)
    {
        printf("T_sa_i node not found.");
        return T_sa_i;
    }
    int T_z_sensor_fault_i = net.FindNode("T_z_sensor_fault_i");
    if (T_z_sensor_fault_i < 0)
    {
        printf("T_z_sensor_fualt_i node not found.");
        return T_z_sensor_fault_i;
    }
    int T_rw_sensor_fault_i = net.FindNode("T_rw_sensor_fault_i");
    if (T_rw_sensor_fault_i < 0)
    {
        printf("T_rw_sensor_fault_i node not found.");
        return T_rw_sensor_fault_i;
    }
    int T_sa_sensor_fault_i = net.FindNode("T_sa_sensor_fault_i");
    if (T_sa_sensor_fault_i < 0)
    {
        printf("T_sa_sensor_fault_i node not found.");
        return T_sa_sensor_fault_i;
    }

    //check BN terminal nodes
    int T_z_f = net.FindNode("T_z_f");
    if (T_z_f < 0)
    {
        printf("T_z_f node not found.");
        return T_z_f;
    }
    int T_w_f = net.FindNode("T_w_f");
    if (T_w_f < 0)
    {
        printf("T_w_f node not found.");
        return T_w_f;
    }
    int T_rw_f = net.FindNode("T_rw_f");
    if (T_rw_f < 0)
    {
        printf("T_rw_f node not found.");
        return T_rw_f;
    }
    int T_sa_f = net.FindNode("T_sa_f");
    if (T_sa_f < 0)
    {
        printf("T_sa_f node not found.");
        return T_sa_f;
    }
    int T_z_sensor_fault_f = net.FindNode("T_z_sensor_fault_f");
    if (T_z_sensor_fault_f < 0)
    {
        printf("T_z_sensor_fualt_f node not found.");
        return T_z_sensor_fault_f;
    }
    int T_rw_sensor_fault_f = net.FindNode("T_rw_sensor_fault_f");
    if (T_rw_sensor_fault_f < 0)
    {
        printf("T_rw_sensor_fault_f node not found.");
        return T_rw_sensor_fault_f;
    }
    int T_sa_sensor_fault_f = net.FindNode("T_sa_sensor_fault_f");
    if (T_sa_sensor_fault_f < 0)
    {
        printf("T_sa_sensor_fault_f node not found.");
        return T_sa_sensor_fault_f;
    }

    printf("Performing update without evidence.\n");
    UpdateAndShowTemporalResults(net);

    // FDD algorithm
    for (int count = 0; count < 238; count ++)//count = 0; count < ds.GetNumberOfRecords() - net.GetNumberOfSlices() + 1    
    {
        printf("Setting evidence from %d to %d records.\n", count, count + net.GetNumberOfSlices() - 1);

        //Setting temporal evidence
        for (int i = 0; i < net.GetNumberOfSlices(); i++)
        {
            //sensor calibration
            resn = net.GetNode(T_z_sensor_cali)->Val()->SetTemporalEvidence(i, ds.GetInt(ds.FindVariable("T_z_sensor_cali"), count + i));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_rw_sensor_cali)->Val()->SetTemporalEvidence(i, ds.GetInt(ds.FindVariable("T_rw_sensor_cali"), count + i));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_sa_sensor_cali)->Val()->SetTemporalEvidence(i, ds.GetInt(ds.FindVariable("T_sa_sensor_cali"), count + i));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
        }
            
            //Sensor values _step 0
            resn = net.GetNode(T_z_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("T_z"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_rw_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("T_rw"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_sa_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("T_sa"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(m_sw_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("x_sw"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_sw_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("T_sw"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(m_sa_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("m_sa"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_o_sensor)->Val()->SetTemporalEvidence(0, ds.GetInt(ds.FindVariable("T_o"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }

        //Sensor values _step 1
            resn = net.GetNode(T_z_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("T_z_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_rw_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("T_rw_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_sa_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("T_sa_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(m_sw_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("x_sw_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_sw_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("T_sw_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(m_sa_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("m_sa_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }
            resn = net.GetNode(T_o_sensor)->Val()->SetTemporalEvidence(1, ds.GetInt(ds.FindVariable("T_o_f"), count));
            if (DSL_OKAY != resn)
            {
                return resn;
            }

        //update BN belief
        UpdateAndShowTemporalResults(net);

        //output FDD results & get terminal nodes
        std::ofstream out("FDD_Output_cor_f.csv", std::fstream::app);
        for (int h = net.GetFirstNode(); h >= 0; h = net.GetNextNode(h))
        {
            if (net.GetTemporalType(h) == dsl_temporalType::dsl_terminalNode)
            {
                DSL_node* node = net.GetNode(h);
                int outcomeCount = node->Def()->GetNumberOfOutcomes();
                const DSL_Dmatrix& mtx = *node->Val()->GetMatrix();
                out << node->GetId() << ",";
                for (int i = 0; i < outcomeCount; i++)
                {
                    out << mtx[i] << ",";
                }
            }
        }
        out << std::endl;

        //update anchor nodes
        const DSL_Dmatrix& mtx_Tz = *net.GetNode(T_z_f)->Val()->GetMatrix();
        resn = net.GetNode(T_z_i)->Def()->SetDefinition({ mtx_Tz });
        if (DSL_OKAY != resn)
        {
            return resn;
        }
        const DSL_Dmatrix& mtx_Tw = *net.GetNode(T_w_f)->Val()->GetMatrix();
        resn = net.GetNode(T_w_i)->Def()->SetDefinition({ mtx_Tw });
        if (DSL_OKAY != resn)
        {
            return resn;
        }
        const DSL_Dmatrix& mtx_Trw = *net.GetNode(T_rw_f)->Val()->GetMatrix();
        resn = net.GetNode(T_rw_i)->Def()->SetDefinition({ mtx_Trw });
        if (DSL_OKAY != resn)
        {
            return resn;
        }
        const DSL_Dmatrix& mtx_Tsa = *net.GetNode(T_sa_f)->Val()->GetMatrix();
        resn = net.GetNode(T_sa_i)->Def()->SetDefinition({ mtx_Tsa });
        if (DSL_OKAY != resn)
        {
            return resn;
        }

        const DSL_Dmatrix& mtx_Tzf = *net.GetNode(T_z_sensor_fault_f)->Val()->GetMatrix();
        resn = net.GetNode(T_z_sensor_fault_i)->Def()->SetDefinition({ mtx_Tzf });
        if (DSL_OKAY != resn)
        {
            return resn;
        }
        const DSL_Dmatrix& mtx_Trwf = *net.GetNode(T_rw_sensor_fault_f)->Val()->GetMatrix();
        resn = net.GetNode(T_rw_sensor_fault_i)->Def()->SetDefinition({ mtx_Trwf });
        if (DSL_OKAY != resn)
        {
            return resn;
        }
        const DSL_Dmatrix& mtx_Tsaf = *net.GetNode(T_sa_sensor_fault_f)->Val()->GetMatrix();
        resn = net.GetNode(T_sa_sensor_fault_i)->Def()->SetDefinition({ mtx_Tsaf });
        if (DSL_OKAY != resn)
        {
            return resn;
        }
    }

    printf("Program complete succesfully!\n");
    return DSL_OKAY;
}

//define functions

static void UpdateAndShowTemporalResults(DSL_network& net)
{
    int resb = net.UpdateBeliefs();
    if (DSL_OKAY != resb)
    {
        printf("UpdateBeliefs failed,\n");
    }
    int sliceCount = net.GetNumberOfSlices();
    for (int h = net.GetFirstNode(); h >= 0; h = net.GetNextNode(h))
    {
        if (net.GetTemporalType(h) == dsl_temporalType::dsl_plateNode)
        {
        }
        else if (net.GetTemporalType(h) == dsl_temporalType::dsl_anchorNode)
        {
            DSL_node* node = net.GetNode(h);
            int outcomeCount = node->Def()->GetNumberOfOutcomes();
            printf("Beliefs for anchor %s:\n", node->GetId());
            const DSL_Dmatrix& mtx = *node->Val()->GetMatrix();
            for (int i = 0; i < outcomeCount; i++)
            {
                printf(" %f", mtx[i]);       
            }
            printf("\n");
        }
        else if (net.GetTemporalType(h) == dsl_temporalType::dsl_terminalNode)
        {
            DSL_node* node = net.GetNode(h);
            int outcomeCount = node->Def()->GetNumberOfOutcomes();
            printf("Beliefs for terminal %s:\n", node->GetId());
            const DSL_Dmatrix& mtx = *node->Val()->GetMatrix();
            for (int i = 0; i < outcomeCount; i++)
            {
                printf(" %f", mtx[i]);
            }
            printf("\n");
        }
        else
        {
        }
    }
    printf("\n");
}


static int CreateCptNode(
    DSL_network& net, const char* id, const char* name,
    std::initializer_list<const char*> outcomes, int xPos, int yPos)
{
    int handle = net.AddNode(DSL_CPT, id);
    DSL_node* node = net.GetNode(handle);
    node->SetName(name);
    node->Def()->SetNumberOfOutcomes(outcomes);
    DSL_rectangle& position = node->Info().Screen().position;
    position.center_X = xPos;
    position.center_Y = yPos;
    position.width = 85;
    position.height = 55;
    return handle;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
