function [f,J,Q] = spm_fx_cmc_BS(x,u,P,M)
% state equations for a Bush and Sejnowksi neural mass model 

% Copyright (C) April 2020 Dimitris Pinotsis & Karl Friston
% Provided under the MIT license

 
% get dimensions and configure state variables
%--------------------------------------------------------------------------
x  = spm_unvec(x,M.x);            % neuronal states
n  = size(x,1);                   % number of sources

% [default] fixed parameters
%--------------------------------------------------------------------------

E  = [1 1/2 1 1/2]*200;           % extrinsic (forward and backward)  

G  = [4 4 8 4 4 2 4 4 8 8]*200 ; % intrinsic connections

T = [2 28 16 28];                 % synaptic time constants
     
R  = 2/3;                         % slope of sigmoid activation function
 
% [specified] fixed parameters
%--------------------------------------------------------------------------
if isfield(M,'pF')
    try, E = M.pF.E; end
    try, G = M.pF.G; end
    try, T = M.pF.T; end
    try, R = M.pF.R; end
end
 
 
% Extrinsic connections
%--------------------------------------------------------------------------
% si = superficial interneurons 
% sp = superficial pyramidal
% dp = deep pyramidal
% ii = inhibitory interneurons
%--------------------------------------------------------------------------
A{1} = exp(P.A{1})*E(1);          % forward  connections (sp -> si)
A{2} = exp(P.A{2})*E(2);          % forward  connections (sp -> dp)
A{3} = exp(P.A{3})*E(3);          % backward connections (dp -> sp)
A{4} = exp(P.A{4})*E(4);          % backward connections (dp -> ii)

% detect and reduce the strength of reciprocal (lateral) connections
%--------------------------------------------------------------------------
for i = 1:length(A)
    L    = (A{i} > exp(-8)) & (A{i}' > exp(-8));
    A{i} = A{i}./(1 + 4*L);
end

% input connections
%--------------------------------------------------------------------------
C    = exp(P.C);
 
% pre-synaptic inputs: s(V)
%--------------------------------------------------------------------------
B    = 0;                        % bias or background (sigmoid)
R    = R.*exp(P.S);              % gain of activation function
F    = 1./(1 + exp(-R*x + B));   % firing rate
S    = F - 1/(1 + exp(B));       % deviation from baseline firing

% input
%==========================================================================
if isfield(M,'u')
    
    % endogenous input
    %----------------------------------------------------------------------
    U = u(:)*512;
    
else
    % exogenous input
    %----------------------------------------------------------------------
    U = C*u(:)*32;
    
end

 
% time constants and intrinsic connections
%==========================================================================
T    = ones(n,1)*T/1000;
G    = ones(n,1)*G;

%--------------------------------------------------------------------------
% G(:,1)  si -> si (-ve self)  4
% G(:,2)  sp -> si*(+ve rec )  4
% G(:,3)  si -> dp (-ve rec )  4 
% G(:,4)  ii -> ii (-ve self)  4
% G(:,5)  sp -> dp (+ve rec )  4 
% G(:,6)  dp -> ii (+ve rec )  2
% G(:,7)  sp -> sp (-ve self)  4
% G(:,8)  si -> sp*(-ve rec )  4
% G(:,9)  ii -> dp (-ve rec )  2
% G(:,10) dp -> dp (-ve self)  1
%--------------------------------------------------------------------------
% Neuronal states (deviations from baseline firing)
%--------------------------------------------------------------------------
%   S(:,1) - voltage     (inhibitory interneurons)
%   S(:,2) - conductance (inhibitory interneurons)
%   S(:,3) - voltage     (superficial pyramidal cells)
%   S(:,4) - conductance (superficial pyramidal cells)
%   S(:,5) - current     (inhibitory interneurons)
%   S(:,6) - conductance (inhibitory interneurons)
%   S(:,7) - voltage     (deep pyramidal cells)
%   S(:,8) - conductance (deep pyramidal cells)
%--------------------------------------------------------------------------
j     = [1 2 3 4];
for i = 1:size(P.T,2)
    T(:,j(i)) = T(:,j(i)).*exp(P.T(:,i));
end


jj     = [1 2 3 4 5 6 7 8 9 10];     % allow all ten connections to change 

for i = 1:size(P.G,2)
    G(:,jj(i)) = G(:,jj(i)).*exp(P.G(:,i));
end

% Modulatory effects of dp depolarisation on intrinsic connection j(1)
%--------------------------------------------------------------------------
if isfield(P,'M')
    G(:,j(1)) = G(:,j(1)).*exp(-P.M*32*S(:,7));
end

 
% Motion of states: f(x)
%--------------------------------------------------------------------------
 
% Conductance
%==========================================================================
 
% Granular layer (inhibitory interneurons)
%--------------------------------------------------------------------------
u      =   A{1}*S(:,3) + U;
u      = - G(:,1).*S(:,1) + G(:,2).*S(:,3) + u;
f(:,2) =  (u - 2*x(:,2) - x(:,1)./T(:,1))./T(:,1);
 
% Supra-granular layer (superficial pyramidal cells)
%--------------------------------------------------------------------------
u      = - A{3}*S(:,7);
u      =  - G(:,8).*S(:,1) - G(:,7).*S(:,3) + u;  
f(:,4) =  (u - 2*x(:,4) - x(:,3)./T(:,2))./T(:,2);
 
% Supra-granular layer (inhibitory interneurons)
%--------------------------------------------------------------------------
u      = - A{4}*S(:,7);
u      =   + G(:,6).*S(:,7) - G(:,4).*S(:,5) + u;
f(:,6) =  (u - 2*x(:,6) - x(:,5)./T(:,3))./T(:,3);
 
% Infra-granular layer (deep pyramidal cells)
%--------------------------------------------------------------------------
u      =   A{2}*S(:,3);
u      = - G(:,3).*S(:,1) + G(:,5).*S(:,3) - G(:,10).*S(:,7) - G(:,9).*S(:,5) + u;
f(:,8) =  (u - 2*x(:,8) - x(:,7)./T(:,4))./T(:,4);
 
% Voltage
%==========================================================================
f(:,1) = x(:,2);
f(:,3) = x(:,4);
f(:,5) = x(:,6);
f(:,7) = x(:,8);
f      = spm_vec(f);
 
 
if nargout < 2; return, end
 
 
%% delays
%==========================================================================
% Delay differential equations can be integrated efficiently (but
% approximately) by absorbing the delay operator into the Jacobian
%
%    dx(t)/dt     = f(x(t - d))
%                 = Q(d)f(x(t))
%
%    J(d)         = Q(d)df/dx
%--------------------------------------------------------------------------
% Implement: dx(t)/dt = f(x(t - d)) = inv(1 + D.*dfdx)*f(x(t))
%                     = Q*f = Q*J*x(t)
%--------------------------------------------------------------------------
[Q,J] = spm_dcm_delay(P,M);
 
return
