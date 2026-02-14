FROM ghcr.io/qwenlm/qwen-code:latest

RUN apt-get update && \
    apt-get install -y openjdk-17-jdk wget unzip && \
    rm -rf /var/lib/apt/lists/*

ENV JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
ENV PATH="${JAVA_HOME}/bin:${PATH}"

RUN java -version

# Install Android SDK
ENV ANDROID_HOME=/opt/android-sdk
RUN mkdir -p ${ANDROID_HOME}/cmdline-tools/latest && \
    cd /tmp && \
    wget -O sdk-tools.zip https://dl.google.com/android/repository/commandlinetools-linux-9477386_latest.zip && \
    unzip sdk-tools.zip -d /tmp/cmdline-extract && \
    mv /tmp/cmdline-extract/cmdline-tools/* ${ANDROID_HOME}/cmdline-tools/latest/ && \
    rm -rf /tmp/cmdline-extract sdk-tools.zip

ENV PATH="${ANDROID_HOME}/cmdline-tools/latest/bin:${ANDROID_HOME}/platform-tools:${PATH}"

# Accept Android SDK licenses
RUN yes | sdkmanager --licenses || true

# Install basic Android platform
RUN sdkmanager "platforms;android-34" "build-tools;34.0.0"