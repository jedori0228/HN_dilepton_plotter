#!/bin/bash
root -l -b -q "src/Draw_CR2.C(false,0)"
root -l -b -q "src/Draw_CR2.C(true,0)"
root -l -b -q src/Draw_CR.C
root -l -b -q src/Draw_SR.C
root -l -b -q "src/Draw_SR.C(1)"
