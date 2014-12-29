Name:       capi-network-bluetooth
Summary:    Network Bluetooth Framework
Version:    0.1.39
Release:    1
Group:      Connectivity/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001:	%{name}.manifest
Source1002:	%{name}-devel.manifest
BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-base-common)
%if "%{bluetooth_frwk}"=="ntb"
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(dbus-1)
BuildRequires:  pkgconfig(gio-2.0)
BuildRequires:  pkgconfig(gio-unix-2.0)
BuildRequires:  pkgconfig(notification)
%if "%{tizen_version}"!="3.0"
BuildRequires:  pkgconfig(aul)
BuildRequires:  pkgconfig(syspopup-caller)
%endif
%else
BuildRequires:  pkgconfig(bluetooth-api)
%endif
BuildRequires:  cmake

%description
Network Bluetooth Framework

%if "%{bluetooth_frwk}"=="ntb"
%package test
Summary:    Test case for Bletooth Framework (DEV)
Requires:   %{name} = %{version}

%description test
Test case for Bluetooth Framework (DEV). Some test programs to test the APIs
and interfaces about Bluetooth Framework or other inner code.
%endif

%package devel
Summary:    Network Bluetooth Framework (DEV)
Group:      Development/Connectivit
Requires:   %{name} = %{version}-%{release}

%description devel
Network Bluetooth Framework.

%devel_desc

%prep
%setup -q
cp %{SOURCE1001} %{SOURCE1002} .

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%if "%{bluetooth_frwk}"=="ntb"
	%if "%{tizen_version}"=="3.0"
		PLUGIN="Tizen3"
	%endif
	%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER} -Dbluetooth_frwk="ntb" -Dplatform=${PLUGIN}
%else
	%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%endif

make %{?jobs:-j%jobs}

%install
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%license LICENSE.APLv2 LICENSE
%{_libdir}/libcapi-network-bluetooth.so.*

%if "%{bluetooth_frwk}"=="ntb"
%files test
%{_libdir}/%{name}-test/bluez-capi-test
%endif

%files devel
%manifest %{name}-devel.manifest
%{_includedir}/network/bluetooth.h
%{_includedir}/network/bluetooth_type.h
%{_libdir}/pkgconfig/capi-network-bluetooth.pc
%{_libdir}/libcapi-network-bluetooth.so

